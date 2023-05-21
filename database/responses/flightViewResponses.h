
#ifndef FLIGHTVIEWRESPONSES_H
#define FLIGHTVIEWRESPONSES_H

#include "database/models/flightModel.h"
#include "database/responses/response.h"

struct FlightResponse : Response
{
    FlightModel *flight;
    FlightResponse(FlightModel *flight, QSqlError *error);
};

#endif // FLIGHTVIEWRESPONSES_H
