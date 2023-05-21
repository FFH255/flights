
#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>

Database::Database(QString driver)
{
    _db = QSqlDatabase::addDatabase(driver);
}

bool Database::connect(QString hostname, int port, QString dbname, QString username, QString password)
{
    if (_db.isOpen())
    {
        return true;
    }

    _db.setHostName(hostname);
    _db.setPort(port);
    _db.setDatabaseName(dbname);
    _db.setUserName(username);
    _db.setPassword(password);

    return _db.open();
}

void Database::disconnect()
{
    _db.close();
}

QString Database::lastError()
{
    return _db.lastError().text();
}

