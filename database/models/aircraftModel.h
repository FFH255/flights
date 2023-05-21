
#ifndef AIRCRAFTMODEL_H
#define AIRCRAFTMODEL_H

#include <QString>

struct AircraftModel
{
    int id;
    QString model;
    int seats;

    AircraftModel(int id, QString model, int seats)
    {
        this->id = id;
        this->model = model;
        this->seats = seats;
    }
};

#endif // AIRCRAFTMODEL_H
