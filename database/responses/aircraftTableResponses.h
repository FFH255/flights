
#ifndef AIRCRAFTTABLERESPONSES_H
#define AIRCRAFTTABLERESPONSES_H

#include "database/models/aircraftModel.h"
#include "database/responses/response.h"

struct AircraftResponse : Response
{
    AircraftModel *aircraft;
    AircraftResponse(AircraftModel *aircraft, QSqlError *error);
};


#endif // AIRCRAFTTABLERESPONSES_H
