
#ifndef TOWN_H
#define TOWN_H

#include "qsqlquerymodel.h"
#include <qstring.h>

struct Town
{
    int id;
    QString name;
    QString country;

    Town(int id, QString name, QString country);
    Town(QSqlQueryModel *model);
};

#endif // TOWN_H
