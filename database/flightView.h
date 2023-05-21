
#ifndef FLIGHTVIEW_H
#define FLIGHTVIEW_H

#include "database/table.h"

class FlightView : Table
{
public:
    FlightView(QObject *parent);

    ModelResponse getModel();
};

#endif // FLIGHTVIEW_H
