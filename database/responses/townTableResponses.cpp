#include "database/responses/townTableResponses.h"



TownResponse::TownResponse(TownModel *town, QSqlError *error) : Response(error)
{
    this->town = town;
}
