#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    QSqlDatabase& getDatabase();
    void createTables();
    void logTransaction(const QString& accountNumber, const QString& transactionType, double amount = 0.0, const QString& details = "");

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
