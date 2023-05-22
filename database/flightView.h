
#ifndef FLIGHTVIEW_H
#define FLIGHTVIEW_H

#include "database/responses/flightViewResponses.h"
#include "database/table.h"

class FlightView : public Table
{
public:
    FlightView(QObject *parent);
    FlightResponse *selectById(int id);
    Response *update(int id, QDate date, QString from, QString to, QString airplane, int price);
};

#endif // FLIGHTVIEW_H
