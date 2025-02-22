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

private:
    DatabaseManager();
    static DatabaseManager* instance;
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
