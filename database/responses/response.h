
#ifndef RESPONSE_H
#define RESPONSE_H

#include "qsqlquery.h"
#include "qsqlquerymodel.h"
#include <QString>

struct Response
{
    QSqlError *error;
    Response(QSqlError *error);
};

struct QueryResponse : Response
{
    QSqlQuery *query;
    QueryResponse(QSqlQuery *query, QSqlError *error);
};

struct ModelResponse : Response
{
    QSqlQueryModel *model;
    ModelResponse(QSqlQueryModel *model, QSqlError *error);
};

#endif // RESPONSE_H
