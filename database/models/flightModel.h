
#ifndef FLIGHTMODEL_H
#define FLIGHTMODEL_H

#include <QString>

struct FlightModel
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
    FlightModel(int id, QString date, QString from, QString to, QString airplane, int price, int reservedTickets, int allTickets, QString status);;
};

#endif // FLIGHTMODEL_H
