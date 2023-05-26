
#include "logger.h"
#include <QMessageBox>

Logger::Logger()
{

}

void Logger::custom(QWidget *parent, QString message, QString debug)
{
    QMessageBox messageBox(parent);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setText(message);
    messageBox.exec();
    if (debug == "")
    {
        qDebug() << message;
    } else
    {
        qDebug() << debug;
    }
}

void Logger::code(QWidget *parent, QSqlError error)
{
    QMessageBox messageBox(parent);

    qDebug() << "NATIVE ERROR CODE:" << error.nativeErrorCode();

    switch(error.type())
    {

    case QSqlError::NoError:
    case QSqlError::ConnectionError:
        messageBox.setWindowTitle("Connection error");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Incorrect login or password");
        break;
    case QSqlError::StatementError:
    case QSqlError::TransactionError:
    case QSqlError::UnknownError:
        break;
    }

    qDebug() << "[FROM LOGGER]: " << error.text();
    messageBox.exec();
}

