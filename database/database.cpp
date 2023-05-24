
#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <qsqlquery.h>

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

int Database::getIdByIndex(const QModelIndex *index)
{
    return index->sibling(index->row(), 0).data().toInt();
}

QSqlQueryModel *Database::query(QString string)
{
    QSqlQuery query = QSqlQuery(QSqlDatabase::database());
    query.exec(string);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    return model;
}


//TOWN


QSqlQueryModel *Database::getAllTowns()
{
    QString queryString = QString("SELECT * FROM town;");
    return query(queryString);
}

QSqlQueryModel *Database::getTownByID(int id)
{
    QString queryString = QString("SELECT * FROM town WHERE id = %1").arg(id);
    return query(queryString);
}

QSqlQueryModel *Database::getTownByIndex(const QModelIndex *index)
{
    int id = getIdByIndex(index);
    return getTownByID(id);
}

QSqlQueryModel *Database::updateTown(int id, QString town, QString country)
{
    QString queryString = QString("CALL update_town(%1, '%2', '%3');")
                              .arg(id)
                              .arg(town)
                              .arg(country);
    return query(queryString);
}


QSqlQueryModel *Database::removeTown(int id)
{
    QString queryString = QString("CALL delete_town(%1)").arg(id);
    return query(queryString);
}

QSqlQueryModel *Database::addTown(QString town, QString country)
{
    QString queryString = QString("CALL insert_town('%1', '%2');")
                              .arg(town)
                              .arg(country);
    return query(queryString);
}


//AIRCRAFT


QSqlQueryModel *Database::getAllAircrafts()
{
    QString queryString = QString("SELECT * FROM airplane;");
    return query(queryString);
}

QSqlQueryModel *Database::getAircraftByID(int id)
{
    QString queryString = QString("SELECT * FROM airplane WHERE id = %1").arg(id);
    return query(queryString);
}

QSqlQueryModel *Database::getAircraftByIndex(const QModelIndex *index)
{
    int id = getIdByIndex(index);
    return getAircraftByID(id);
}

QSqlQueryModel *Database::updateAircraft(int id, QString name, int seats)
{
    QString queryString = QString("CALL update_airplane(%1, '%2', %3::smallint);")
                              .arg(id)
                              .arg(name)
                              .arg(seats);
    return query(queryString);
}

QSqlQueryModel *Database::removeAircraft(int id)
{
    QString queryString = QString("CALL delete_airplane(%1);").arg(id);
    return query(queryString);
}

QSqlQueryModel *Database::addAircraft(QString name, int seats)
{
    QString queryString = QString("CALL insert_airplane('%1'::varchar(32), %2::smallint);")
                              .arg(name)
                              .arg(seats);
    return query(queryString);
}

QSqlQueryModel *Database::getAvailableModels(QString date)
{
    QString queryString = QString("SELECT * FROM select_available_airplane_models('%1'::date);")
                              .arg(date);
    return query(queryString);
}


//FLIGHTS


QSqlQueryModel *Database::getAllFlights()
{
    QString queryString = QString("SELECT * FROM flight_view");
    return query(queryString);
}

QSqlQueryModel *Database::getFlightByID(int id)
{
    QString queryString = QString("SELECT * FROM flight_view WHERE id = %1").arg(id);
    return query(queryString);
}

QSqlQueryModel *Database::getFlightByIndex(const QModelIndex *index)
{
    int id = getIdByIndex(index);
    return getFlightByID(id);
}

QSqlQueryModel *Database::updateFlight(int id, QString date, QString from, QString to, QString airplane, int price)
{
    QString queryString = QString("CALL update_flight_view(%1, '%2'::date, '%3', '%4', '%5', %6);")
                              .arg(id)
                              .arg(date)
                              .arg(from)
                              .arg(to)
                              .arg(airplane)
                              .arg(price);
    return query(queryString);
}

QSqlQueryModel *Database::removeFlight(int id)
{
    QString queryString = QString("CALL delete_flight_view(%1)").arg(id);
    return query(queryString);
}

QSqlQueryModel *Database::addFlight(QString date, QString from, QString to, QString airplane, int price)
{
    QString queryString = QString("CALL insert_flight_view('%1'::date, '%2', '%3', '%4', %5);")
                              .arg(date)
                              .arg(from)
                              .arg(to)
                              .arg(airplane)
                              .arg(price);
    return query(queryString);
}

