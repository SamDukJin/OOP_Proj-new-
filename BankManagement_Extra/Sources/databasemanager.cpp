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

    // Ensure the accounts table exists
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
            if (columnName == "status") statusExists = true;  // Check for status
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
}




