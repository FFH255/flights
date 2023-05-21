#include "database/models/flightModel.h"



FlightModel::FlightModel(int id, QDate date, QString from, QString to, QString airplane, int price, int reservedTickets, int allTickets, QString status)
{
    this->id = id;
    this->date = date;
    this->from = from;
    this->to = to;
    this->airplane = airplane;
    this->price = price;
    this->reservedTickets = reservedTickets;
    this->allTickets = allTickets;
    this->status = status;
}
