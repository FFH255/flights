#include "townTable.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

TownTable::TownTable(QObject *parent) : Table(parent)
{

}

TownTable::~TownTable()
{

}

ModelResponse *TownTable::getModel()
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new ModelResponse(nullptr, res->error);
    }

    QSqlQuery *query = res->query;
    bool ok = query->exec("SELECT * FROM town;");

    if (!ok)
    {
        return new ModelResponse(nullptr, res->error);
    }

    QSqlQueryModel *model = new QSqlQueryModel(this->parent);
    model->setQuery(std::move(*query));
    return new ModelResponse(model, nullptr);
}

TownResponse *TownTable::selectById(int id)
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new TownResponse(nullptr, res->error);
    }

    QSqlQuery *query = res->query;
    QString queryString = QString("SELECT * FROM town WHERE id = %1;")
                              .arg(id);
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new TownResponse(nullptr, new QSqlError(query->lastError()));
    }

    query->next();
    int index = query->value(0).toInt();
    QString name = query->value(1).toString();
    QString country = query->value(2).toString();
    
    return new TownResponse(new TownModel(index, name, country), nullptr);
}

 Response *TownTable::updateById(int id, QString town, QString country)
{
    QueryResponse *res = getQuery();
    QString queryString = QString("CALL update_town(%1, '%2', '%3');")
                              .arg(id)
                              .arg(town)
                              .arg(country);
    if (res->error != nullptr) {
        return res;
    }

    QSqlQuery *query = res->query;
    if (!query->exec(queryString))
    {
        return new Response(new QSqlError(query->lastError()));
    }

    return new Response(nullptr);
}

Response *TownTable::deteleById(int id)
{
    QueryResponse *res = getQuery();
    QString queryString = QString("CALL delete_town(%1)").arg(id);

    if (res->error != nullptr)
    {
        return res;
    }

    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }

    return new Response(nullptr);
}

Response *TownTable::insert(QString town, QString country)
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new Response(res->error);
    }

    QString queryString = QString("CALL insert_town('%1', '%2');")
                              .arg(town)
                              .arg(country);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }

    return new Response(nullptr);
}
