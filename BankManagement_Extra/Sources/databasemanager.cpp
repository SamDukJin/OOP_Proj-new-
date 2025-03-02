#include "databasemanager.h"

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bank_system.db");

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return;
    }

    createTables();
}

DatabaseManager* DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}

QSqlDatabase& DatabaseManager::getDatabase() {
    return db;
}

void DatabaseManager::createTables() {
    QSqlQuery query(db);

    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS accounts (
            account_name TEXT NOT NULL,
            account_number TEXT PRIMARY KEY,
            account_password TEXT NOT NULL
        )
    )")) {
        qDebug() << "Failed to create accounts table:" << query.lastError().text();
    }

    // Check existing columns
    QSqlQuery checkQuery(db);
    checkQuery.prepare("PRAGMA table_info(accounts)");
    if (checkQuery.exec()) {
        bool balanceExists = false;
        bool loanExists = false;
        bool statusExists = false;
        bool loanStatusExists = false;

        while (checkQuery.next()) {
            QString columnName = checkQuery.value(1).toString();
            if (columnName == "account_balance") balanceExists = true;
            if (columnName == "account_loan") loanExists = true;
            if (columnName == "status") statusExists = true;
            if (columnName == "loan_status") loanStatusExists = true;
        }

        // Add account_balance if missing
        if (!balanceExists) {
            QSqlQuery alterQuery(db);
            if (!alterQuery.exec("ALTER TABLE accounts ADD COLUMN account_balance FLOAT DEFAULT 0.0")) {
                qDebug() << "Failed to add account_balance column:" << alterQuery.lastError().text();
            }
        }

        // Add account_loan if missing
        if (!loanExists) {
            QSqlQuery alterQuery(db);
            if (!alterQuery.exec("ALTER TABLE accounts ADD COLUMN account_loan FLOAT DEFAULT 0.0")) {
                qDebug() << "Failed to add account_loan column:" << alterQuery.lastError().text();
            }
        }

        // Add status column if missing
        if (!statusExists) {
            QSqlQuery alterQuery(db);
            if (!alterQuery.exec("ALTER TABLE accounts ADD COLUMN status TEXT DEFAULT 'active'")) {
                qDebug() << "Failed to add status column:" << alterQuery.lastError().text();
            } else {
                qDebug() << "status column added successfully!";
            }
        }
        if (!loanStatusExists) {
            QSqlQuery alterQuery(db);
            if (!alterQuery.exec("ALTER TABLE accounts ADD COLUMN loan_status TEXT DEFAULT 'paid'")) {
                qDebug() << "Failed to add loan_status column:" << alterQuery.lastError().text();
            } else {
                qDebug() << "loan_status column added successfully!";
            }
        }
    } else {
        qDebug() << "Failed to check table structure:" << checkQuery.lastError().text();
    }

    // Create transactions table
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account_number TEXT NOT NULL,
            transaction_type TEXT NOT NULL,
            amount REAL DEFAULT NULL,
            details TEXT DEFAULT NULL,
            date_time DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (account_number) REFERENCES accounts(account_number)
        )
    )")) {
        qDebug() << "Failed to create transactions table:" << query.lastError().text();
    }
}

void DatabaseManager::logTransaction(const QString& accountNumber, const QString& transactionType, double amount, const QString& details) {
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO transactions (account_number, transaction_type, amount, details)
        VALUES (:account_number, :transaction_type, :amount, :details)
    )");
    query.bindValue(":account_number", accountNumber);
    query.bindValue(":transaction_type", transactionType);
    query.bindValue(":amount", amount);
    query.bindValue(":details", details);

    if (!query.exec()) {
        qDebug() << "Failed to log transaction:" << query.lastError().text();
    }
}
