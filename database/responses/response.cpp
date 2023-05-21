
#include "response.h"

Response::Response(QSqlError *error)
{
    this ->error = error;
}


QueryResponse::QueryResponse(QSqlQuery *query, QSqlError *error) : Response(error)
{
    this->query = query;
}

ModelResponse::ModelResponse(QSqlQueryModel *model, QSqlError *error) : Response(error)
{
    this->model = model;
}
