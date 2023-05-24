
#ifndef DATABASE_H
#define DATABASE_H
#include "qsqlquerymodel.h"
#include <QString>
#include <qsqldatabase.h>

class Database
{

private:
    QSqlDatabase _db;
    static QSqlQueryModel *query(QString string);

public:
    Database(QString driver);
    bool connect(QString hostname, int port, QString dbname, QString username, QString password);
    void disconnect();

    static int getIdByIndex(const QModelIndex *index);

    //town
    static QSqlQueryModel *getAllTowns();
    static QSqlQueryModel *getTownByID(int id);
    static QSqlQueryModel *getTownByIndex(const QModelIndex *index);
    static QSqlQueryModel *updateTown(int id, QString town, QString country);
    static QSqlQueryModel *removeTown(int id);
    static QSqlQueryModel *addTown(QString town, QString country);

    //aircraft
    static QSqlQueryModel *getAllAircrafts();
    static QSqlQueryModel *getAircraftByID(int id);
    static QSqlQueryModel *getAircraftByIndex(const QModelIndex *index);
    static QSqlQueryModel *updateAircraft(int id, QString name, int seats);
    static QSqlQueryModel *removeAircraft(int id);
    static QSqlQueryModel *addAircraft(QString name, int seats);
    static QSqlQueryModel *getAvailableModels(QString date);

    //flight
    static QSqlQueryModel *getAllFlights();
    static QSqlQueryModel *getFlightByID(int id);
    static QSqlQueryModel *getFlightByIndex(const QModelIndex *index);
    static QSqlQueryModel *updateFlight(int id, QString date, QString from, QString to, QString airplane, int price);
    static QSqlQueryModel *removeFlight(int id);
    static QSqlQueryModel *addFlight(QString date, QString from, QString to, QString airplane, int price);
};

#endif // DATABASE_H
