
#ifndef TABLE_H
#define TABLE_H

#include "database/responses/response.h"
#include "qobject.h"

class Table
{
protected:
    QObject *parent;

public:
    Table(QObject *parent = nullptr);
    ~Table();

protected:
    QueryResponse *getQuery();
};

#endif // TABLE_H
