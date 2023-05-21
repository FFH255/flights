
#ifndef TOWNTABLERESPONSES_H
#define TOWNTABLERESPONSES_H

#include "database/responses/response.h"
#include "database/models/townModel.h"

struct TownResponse : Response
{
    TownModel *town;
    TownResponse(TownModel *town, QSqlError *error);
};

struct TownsResponse : Response
{
    QList<TownModel*> *towns;
    TownsResponse(QList<TownModel*> *towns, QSqlError *error);
};

#endif // TOWNTABLERESPONSES_H
