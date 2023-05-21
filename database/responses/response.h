
#ifndef RESPONSE_H
#define RESPONSE_H

#include "qsqlquery.h"
#include "qsqlquerymodel.h"
#include <QString>

struct Response
{
    bool ok;
    QString errorMessage;
};

struct QueryResponse : Response
{
    QSqlQuery *query;
};

struct ModelResponse : Response
{
    QSqlQueryModel *model;
};


#endif // RESPONSE_H
