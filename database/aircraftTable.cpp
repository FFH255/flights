
#include "aircraftTable.h"
#include "qsqlerror.h"

AircraftTable::AircraftTable(QObject *parent)
    : Table{parent}
{

}

ModelResponse *AircraftTable::getModel()
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new ModelResponse(nullptr, res->error);
    }

    QSqlQuery *query = res->query;
    bool ok = query->exec("SELECT * FROM airplane");

    if (!ok)
    {
        return new ModelResponse(nullptr, new QSqlError(query->lastError()));
    }

    QSqlQueryModel *model = new QSqlQueryModel(parent);
    model->setQuery(std::move(*query));
    return new ModelResponse(model, nullptr);
}

AircraftResponse *AircraftTable::selectById(int id)
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new AircraftResponse(nullptr, res->error);
    }
    QString queryString = QString("SELECT * FROM airplane WHERE id = %1").arg(id);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new AircraftResponse(nullptr, new QSqlError(query->lastError()));
    }
    query->next();
    int index = query->value(0).toInt();
    QString name = query->value(1).toString();
    int seats = query->value(2).toInt();

    return new AircraftResponse(new AircraftModel(index, name, seats), nullptr);
}

Response *AircraftTable::updateById(int id, QString name, int seats)
{
    QueryResponse *res = getQuery();
    if (res->error != nullptr)
    {
        return new Response(res->error);
    }
    QString queryString = QString("CALL update_airplane(%1, '%2', %3::smallint);")
                              .arg(id)
                              .arg(name)
                              .arg(seats);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);
    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }
    return new Response(nullptr);
}

Response *AircraftTable::insert(QString name, int seats)
{
    QueryResponse *res = getQuery();

    if(res->error != nullptr)
    {
        return new Response(res->error);
    }
    QString queryString = QString("CALL insert_airplane('%1'::varchar(32), %2::smallint);")
                              .arg(name)
                              .arg(seats);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }
    return new Response(nullptr);
}

Response *AircraftTable::deteleById(int id)
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new Response(res->error);
    }
    QString queryString = QString("CALL delete_airplane(%1);").arg(id);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }
    return new Response(nullptr);
}
