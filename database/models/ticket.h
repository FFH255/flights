
#ifndef TICKET_H
#define TICKET_H

#include "qsqlquerymodel.h"
#include <qstring.h>

struct Ticket
{
    int id;
    QString flightDate;
    QString from;
    QString to;
    int price;
    QString bookingDate;

    Ticket(int id, QString flightDate, QString from, QString to, int price, QString bookingDate);
    Ticket(QSqlQueryModel *model);
};

#endif // TICKET_H
