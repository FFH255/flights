
#include "table.h"
#include "qsqlerror.h"

Table::Table(QString tableName, QObject *parent)
{
    this->tableName = tableName;
    this->parent = parent;
}

Table::~Table()
{
    delete parent;
}

QueryResponse *Table::getQuery()
{
    QSqlDatabase database = QSqlDatabase::database();

    if (!database.isOpen())
    {
        return new QueryResponse(nullptr, new QSqlError(database.lastError()));
    }
    QSqlQuery *query = new QSqlQuery(database);
    return new QueryResponse(query, nullptr);
}

ModelResponse *Table::getModel()
{
    QueryResponse *res = getQuery();

    if (res->error)
    {
        ModelResponse *modelResponse = new ModelResponse(nullptr, res->error);
        delete res;
        return modelResponse;
    }
    QString queryString = QString("SELECT * FROM %1").arg(this->tableName);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        ModelResponse *modelResponse = new ModelResponse(nullptr, new QSqlError(query->lastError()));
        delete res;
        return modelResponse;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this->parent);
    model->setQuery(std::move(*query));
    delete res;
    return new ModelResponse(model, nullptr);
}

