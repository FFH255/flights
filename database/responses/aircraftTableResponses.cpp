
#include "aircraftTableResponses.h"

AircraftResponse::AircraftResponse(AircraftModel *aircraft, QSqlError *error) : Response(error)
{
    this->aircraft = aircraft;
}

AvailableModelsResponse::AvailableModelsResponse(QList<QString> *models, QSqlError *error) : Response(error)
{
    this->models = models;
}
