
#ifndef TOWNMODEL_H
#define TOWNMODEL_H

#include <QString>

struct TownModel
{
    int id;
    QString name;
    QString country;

    TownModel(int id, QString name, QString country) {
        this->id = id;
        this->name = name;
        this->country = country;
    }
};

#endif // TOWNMODEL_H
