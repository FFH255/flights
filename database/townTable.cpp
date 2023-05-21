#include "townTable.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

TownTable::TownTable(QObject *parent) : Table(parent)
{

}

TownTable::~TownTable()
{

}

ModelResponse TownTable::getModel()
{
    ModelResponse result;
    QueryResponse res = getQuery();

    if (!res.ok)
    {
        return result = {{false, res.errorMessage}, nullptr};
    }

    QSqlQuery *query = res.query;
    bool ok = query->exec("SELECT * FROM town;");

    if (!ok)
    {
        return result = {{ok, query->lastError().text()}, nullptr};
    }

    QSqlQueryModel *model = new QSqlQueryModel(this->parent);
    model->setQuery(std::move(*query));
    return result = {{true, ""}, model};
}

TownResponse TownTable::selectById(int id)
{
    TownResponse result;

    QueryResponse res = getQuery();

    if (!res.ok)
    {
        return result = {{false, res.errorMessage}, nullptr};
    }

    QSqlQuery *query = res.query;

    QString queryString = QString("SELECT * FROM town WHERE id = %1;")
                              .arg(id);

    bool ok = query->exec(queryString);

    if (!ok)
    {
        return result = {{false, query->lastError().text()}, nullptr};
    }

    query->next();

    int index = query->value(0).toInt();
    QString name = query->value(1).toString();
    QString country = query->value(2).toString();
    
    return result = {{true, ""}, new TownModel(index, name, country)};
}

 Response TownTable::updateById(int id, QString town, QString country)
{
    Response result;
    QueryResponse res = getQuery();
    QString queryString = QString("CALL update_town(%1, '%2', '%3');")
                              .arg(id)
                              .arg(town)
                              .arg(country);
    if (!res.ok) {
        return res;
    }

    QSqlQuery *query = res.query;
    if (!query->exec(queryString))
    {
        return result = {false, query->lastError().text()};
    }

    return result = {true, ""};
}

Response TownTable::deteleById(int id)
{
    Response response;
    QueryResponse res = getQuery();
    QString queryString = QString("CALL delete_town(%1)").arg(id);

    if (!res.ok)
    {
        return res;
    }

    QSqlQuery *query = res.query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return response = {false, query->lastError().text()};
    }

    return response = {true, ""};
}

Response TownTable::insert(QString town, QString country)
{
    Response response;
    QueryResponse res = getQuery();

    if (!res.ok)
    {
        return response = {false, res.errorMessage};
    }

    QString queryString = QString("CALL insert_town('%1', '%2');")
                              .arg(town)
                              .arg(country);
    QSqlQuery *query = res.query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return response = {false, query->lastError().text()};
    }

    return response = {true, ""};
}

