
#include "flightViewResponses.h"

FlightResponse::FlightResponse(FlightModel *flight, QSqlError *error) : Response(error)
{
    this->flight = flight;
}
