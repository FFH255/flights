
#include "table.h"

Table::Table(QObject *parent)
{
    this->parent = parent;
}

Table::~Table()
{
    delete parent;
}

QueryResponse Table::getQuery()
{
    QueryResponse res;
    QSqlDatabase database = QSqlDatabase::database();

    if (!database.isOpen())
    {
        return res = {{false, "Database is now opened."}, nullptr};
    }
    QSqlQuery *query = new QSqlQuery(database);
    return res = {{true, ""}, query};
}

