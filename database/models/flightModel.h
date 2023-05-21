
#ifndef FLIGHTMODEL_H
#define FLIGHTMODEL_H

#include "qdatetime.h"
struct FlightModel
{
    int id;
    QDate date;
    QString from;
    QString to;
    QString airplane;
    int price;
    int reservedTickets;
    int allTickets;
    QString status;
    FlightModel(int id, QDate date, QString from, QString to, QString airplane, int price, int reservedTickets, int allTickets, QString status);;
};

#endif // FLIGHTMODEL_H
