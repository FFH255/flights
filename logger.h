
#ifndef LOGGER_H
#define LOGGER_H

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
    static void exec(QWidget *parent, MessageType type, QString message, QString debug = "");
};

#endif // LOGGER_H
