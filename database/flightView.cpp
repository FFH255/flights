#include "flightView.h"
#include "qdatetime.h"
#include "qsqlerror.h"

FlightView::FlightView(QObject *parent) : Table("flight_view", parent)
{

}

FlightResponse *FlightView::selectById(int id)
{
    QueryResponse *res = getQuery();

    if (res->error != nullptr)
    {
        return new FlightResponse(nullptr, res->error);
    }
    QString queryString = QString("SELECT * FROM flight_view WHERE id = %1").arg(id);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new FlightResponse(nullptr, new QSqlError(query->lastError()));
    }
    query->next();
    int index = query->value(0).toInt();
    QString date = query->value(1).toDate().toString("yyyy-MM-dd");
    QString from = query->value(2).toString();
    QString to = query->value(3).toString();
    QString airplane = query->value(4).toString();
    int price = query->value(5).toInt();
    int reservedTickets = query->value(6).toInt();
    int allTickets = query->value(7).toInt();
    QString status = query->value(8).toString();

    return new FlightResponse(new FlightModel(index, date, from, to, airplane, price, reservedTickets, allTickets, status), nullptr);
}

Response *FlightView::update(int id, QString date, QString from, QString to, QString airplane, int price)
{
    QueryResponse *res = getQuery();

    if (res->error)
    {
        return new Response(res->error);
    }
    QString queryString = QString("CALL update_flight_view(%1, '%2'::date, '%3', '%4', '%5', %6);")
                              .arg(id)
                              .arg(date)
                              .arg(from)
                              .arg(to)
                              .arg(airplane)
                              .arg(price);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }
    return new Response(nullptr);
}

Response *FlightView::insert(QString date, QString from, QString to, QString airplane, int price)
{
    QueryResponse *res = getQuery();

    if (res->error)
    {
        return new Response(res->error);
    }
    QString queryString = QString("CALL insert_flight_view('%1'::date, '%2', '%3', '%4', %5);")
                              .arg(date)
                              .arg(from)
                              .arg(to)
                              .arg(airplane)
                              .arg(price);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }
    return new Response(nullptr);
}

Response *FlightView::deleteById(int id)
{
    QueryResponse *res = getQuery();

    if (res->error)
    {
        return new Response(res->error);
    }
    QString queryString = QString("CALL delete_flight_view(%1)").arg(id);
    QSqlQuery *query = res->query;
    bool ok = query->exec(queryString);

    if (!ok)
    {
        return new Response(new QSqlError(query->lastError()));
    }
    return new Response(nullptr);
}













