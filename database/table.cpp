
#include "table.h"
#include "qsqlerror.h"

Table::Table(QObject *parent)
{
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

