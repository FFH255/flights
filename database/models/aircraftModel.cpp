#include "database/models/aircraftModel.h"

AircraftModel::AircraftModel(int id, QString model, int seats)
{
    this->id = id;
    this->model = model;
    this->seats = seats;
}
