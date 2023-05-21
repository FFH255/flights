
#ifndef FLIGHTVIEW_H
#define FLIGHTVIEW_H

#include "database/responses/flightViewResponses.h"
#include "database/table.h"

class FlightView : public Table
{
public:
    FlightView(QObject *parent);
    FlightResponse *selectById(int id);
};

#endif // FLIGHTVIEW_H
