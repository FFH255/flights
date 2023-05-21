
#ifndef TOWNTABLE_H
#define TOWNTABLE_H

#include "database/responses/townTableResponses.h"
#include "database/table.h"

class TownTable : Table
{

public:
    TownTable(QObject *parent = nullptr);
    ~TownTable();

    ModelResponse *getModel();
    TownResponse *selectById(int id);
    Response *updateById(int id, QString town, QString country);
    Response *deteleById(int id);
    Response *insert(QString town, QString country);
};

#endif // TOWNTABLE_H
