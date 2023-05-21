
#ifndef TOWNTABLERESPONSES_H
#define TOWNTABLERESPONSES_H

#include "database/responses/response.h"
#include "database/models/townModel.h"

struct TownResponse : Response
{
    TownModel *town;
    TownResponse(TownModel *town, QSqlError *error);
};

#endif // TOWNTABLERESPONSES_H
