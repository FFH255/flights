
#ifndef LOGGER_H
#define LOGGER_H

#include "qsqlerror.h"
#include "qwidget.h"

enum MessageType
{
    ServerFail,
    ConnectionFail,
    AuthFail,
    MissingValue,
    BadValue,
    SameValue
};

class Logger
{

public:
    Logger();
    static void custom(QWidget *parent, QString message, QString debug = "");
    static void code(QWidget *parent, QSqlError error);
};

#endif // LOGGER_H
