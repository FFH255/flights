
#include "ticket.h"
#include "qsqlrecord.h"

Ticket::Ticket(int id, QString flightDate, QString from, QString to, int price, QString bookingDate)
{
    this->id = id;
    this->flightDate = flightDate;
    this->from = from;
    this->to = to;
    this->price = price;
    this->bookingDate = bookingDate;
}

Ticket::Ticket(QSqlQueryModel *model)
{
    QSqlRecord record = model->record(0);
    this->id = record.value("id").toInt();
    this->flightDate = record.value("flight_date").toString();
    this->from = record.value("from").toString();
    this->to = record.value("to").toString();
    this->price = record.value("price").toInt();
    this->bookingDate = record.value("booking_date").toString();
}

