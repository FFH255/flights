
#include "aircraftTable.h"
#include "qsqlerror.h"

AircraftTable::AircraftTable(QObject *parent)
    : Table{parent}
{

}

ModelResponse AircraftTable::getModel()
{
    ModelResponse result;
    QueryResponse res = getQuery();

    if (!res.ok)
    {
        return result = {{false, res.errorMessage}, nullptr};
    }

    QSqlQuery *query = res.query;
    bool ok = query->exec("SELECT * FROM airplane");

    if (!ok)
    {
        return result = {{false, query->lastError().text()}, nullptr};
    }

    QSqlQueryModel *model = new QSqlQueryModel(parent);
    model->setQuery(std::move(*query));
    return result = {{true, ""}, model};
}

AircraftResponse AircraftTable::selectById(int id)
{
    AircraftResponse result;
    QueryResponse res = getQuery();

    if (!res.ok)
    {
        return result = {{false, res.errorMessage}, nullptr};
    }
    QString queryString = QString("SELECT * FROM airplane WHERE id = %1").arg(id);
    QSqlQuery *query = res.query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return result = {{false, query->lastError().text()}, nullptr};
    }
    query->next();
    int index = query->value(0).toInt();
    QString name = query->value(1).toString();
    int seats = query->value(2).toInt();
    return result = {{true, ""}, new AircraftModel(index, name, seats)};
}

Response AircraftTable::updateById(int id, QString name, int seats)
{
    Response result;
    QueryResponse res = getQuery();
    if (!res.ok)
    {
        return result = {false, res.errorMessage};
    }
    QString queryString = QString("CALL update_airplane(%1, '%2', %3::smallint);")
                              .arg(id)
                              .arg(name)
                              .arg(seats);
    QSqlQuery *query = res.query;
    bool ok = query->exec(queryString);
    if (!ok)
    {
        return result = {false, query->lastError().text()};
    }
    return result = {true, ""};
}

Response AircraftTable::insert(QString name, int seats)
{
    Response result;
    QueryResponse res = getQuery();

    if(!res.ok)
    {
        return result = {false, res.errorMessage};
    }
    QString queryString = QString("CALL insert_airplane('%1'::varchar(32), %2::smallint);")
                              .arg(name)
                              .arg(seats);
    QSqlQuery *query = res.query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return result = {false, query->lastError().text()};
    }
    return result = {true, ""};
}

Response AircraftTable::deteleById(int id)
{
    Response result;
    QueryResponse res = getQuery();

    if (!res.ok)
    {
        return result = {false, res.errorMessage};
    }
    QString queryString = QString("CALL delete_airplane(%1);").arg(id);
    QSqlQuery *query = res.query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return result = {false, query->lastError().text()};
    }
    return result = {true, ""};
}

