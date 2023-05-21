
#ifndef TABLE_H
#define TABLE_H

#include "database/responses/response.h"
#include "qobject.h"

class Table
{
protected:
    QObject *parent;
    QString tableName;

protected:
    QueryResponse *getQuery();

public:
    Table(QString tableName, QObject *parent = nullptr);
    ~Table();

    ModelResponse *getModel();

};

#endif // TABLE_H
