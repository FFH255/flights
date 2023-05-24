
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "qsqlquerymodel.h"
#include <qstring.h>

struct Aircraft
{
    int id;
    QString model;
    int seats;

    Aircraft(int id, QString model, int seats);
    Aircraft(QSqlQueryModel *model);
};

#endif // AIRCRAFT_H
