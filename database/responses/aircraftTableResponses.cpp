
#include "aircraftTableResponses.h"

AircraftResponse::AircraftResponse(AircraftModel *aircraft, QSqlError *error) : Response(error)
{
    this->aircraft = aircraft;
}
