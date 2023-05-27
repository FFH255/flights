
#ifndef FLIGHT_H
#define FLIGHT_H

#include "qsqlquerymodel.h"
#include <qstring.h>

struct Flight
{
    int id;
    QString date;
    QString from;
    QString to;
    QString airplane;
    int price;
    int reservedTickets;
    int allTickets;
    QString status;
    QString lastUpdated;
    Flight(int id, QString date, QString from, QString to, QString airplane, int price, int reservedTickets, int allTickets, QString status, QString lastUpdated);
    Flight(QSqlQueryModel *model);
};

#endif // FLIGHT_H
