
#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSqlDatabase.h>

class Database
{

private:
    QSqlDatabase _db;

public:
    Database(QString driver);
    bool connect(QString hostname, int port, QString dbname, QString username, QString password);
    void disconnect();
    QString lastError();
};

#endif // DATABASE_H
