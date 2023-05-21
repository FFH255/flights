
#ifndef TOWNTABLE_H
#define TOWNTABLE_H

#include "database/responses/townTableResponses.h"
#include "database/table.h"

class TownTable : public Table
{

public:
    TownTable(QObject *parent = nullptr);
    ~TownTable();

    TownResponse *selectById(int id);
    TownsResponse *selectAll();
    Response *updateById(int id, QString town, QString country);
    Response *deteleById(int id);
    Response *insert(QString town, QString country);
};

#endif // TOWNTABLE_H
