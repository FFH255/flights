
#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QString>

struct ScheduleModel
{
    int id;
    QString date;
    QString from;
    QString to;
    ScheduleModel(int id, QString date, QString from, QString to);
};

#endif // SCHEDULEMODEL_H
