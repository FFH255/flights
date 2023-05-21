
#ifndef TOWNMODEL_H
#define TOWNMODEL_H

#include <QString>

struct TownModel
{
    int id;
    QString name;
    QString country;

    TownModel(int id, QString name, QString country);
};

#endif // TOWNMODEL_H
