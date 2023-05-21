
#ifndef AIRCRAFTMODEL_H
#define AIRCRAFTMODEL_H

#include <QString>

struct AircraftModel
{
    int id;
    QString model;
    int seats;

    AircraftModel(int id, QString model, int seats);
};

#endif // AIRCRAFTMODEL_H
