
#include "flight.h"
#include "qdatetime.h"
#include "qsqlrecord.h"

Flight::Flight(int id, QString date, QString from, QString to, QString airplane, int price, int reservedTickets, int allTickets, QString status)
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

Flight::Flight(QSqlQueryModel *model)
{
    QSqlRecord record = model->record(0);
    this->id = record.value("id").toInt();
    this->date = record.value("date").toDate().toString("yyyy-MM-dd");
    this->from = record.value("from").toString();
    this->to = record.value("to").toString();
    this->airplane = record.value("airplane").toString();
    this->price = record.value("price").toInt();
    this->reservedTickets = record.value("reserved_tickets").toInt();
    this->allTickets = record.value("all_tickets").toInt();
    this->status = record.value("status").toString();
}

