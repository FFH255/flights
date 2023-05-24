
#include "aircraft.h"
#include "qsqlrecord.h"

Aircraft::Aircraft(int id, QString model, int seats)
{
    this->id = id;
    this->model = model;
    this->seats = seats;
}

Aircraft::Aircraft(QSqlQueryModel *model)
{
    QSqlRecord record = model->record(0);
    this->id = record.value("id").toInt();
    this->model = record.value("model").toString();
    this->seats = record.value("seats").toInt();
}

