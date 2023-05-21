
#include "logger.h"
#include <QMessageBox>

Logger::Logger()
{

}

void Logger::exec(QWidget *parent, MessageType type, QString message, QString debug)
{
    QMessageBox messageBox = QMessageBox(parent);
    QString title;

    switch(type)
    {
    case ServerFail:
        title = QString("Server Fail");
        messageBox.setIcon(QMessageBox::Warning);
        break;
    case ConnectionFail:
        title = QString("Connection Fail");
        messageBox.setIcon(QMessageBox::Warning);
        break;
    case AuthFail:
        title = QString("Auth Fail");
        messageBox.setIcon(QMessageBox::Warning);
        break;
    case MissingValue:
        title = QString("Missing Value");
        messageBox.setIcon(QMessageBox::Information);
        break;
    case BadValue:
        title = QString("Bad Value");
        messageBox.setIcon(QMessageBox::Information);
        break;
    case SameValue:
        title = QString("Same Value");
        messageBox.setIcon(QMessageBox::Information);
        break;
    }

    messageBox.setWindowTitle(title);
    messageBox.setText(message);
    messageBox.exec();

    if (debug != "")
    {
        qDebug() << debug;
    }
}

