
#ifndef AIRCRAFTTABLE_H
#define AIRCRAFTTABLE_H

#include "database/responses/aircraftTableResponses.h"
#include "table.h"

class AircraftTable : public Table
{

public:
    explicit AircraftTable(QObject *parent = nullptr);

    AircraftResponse *selectById(int id);
    Response *updateById(int id, QString name, int seats);
    Response *insert(QString name, int seats);
    Response *deteleById(int id);
    AvailableModelsResponse *selectAvailableModels(QDate date);
};

#endif // AIRCRAFTTABLE_H
