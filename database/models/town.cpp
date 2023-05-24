#include "town.h"
#include "qsqlrecord.h"

Town::Town(int id, QString name, QString country)
{
    this->id = id;
    this->name = name;
    this->country = country;
}

Town::Town(QSqlQueryModel *model)
{
    QSqlRecord record = model->record(0);
    this->id = record.value("id").toInt();
    this->name = record.value("name").toString();
    this->country = record.value("country").toString();
}

