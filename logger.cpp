
#include "logger.h"
#include <QMessageBox>

Logger::Logger()
{

}

void Logger::custom(QWidget *parent, QString message, QString debug)
{
    QMessageBox messageBox(parent);
    messageBox.setWindowTitle("Внимание");
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

    qDebug() << "[КОД ОШИБКИ]:" << error.nativeErrorCode();

    switch(error.nativeErrorCode().toInt())
    {
    case CustomErrorCodes::UniqueValue:
        messageBox.setWindowTitle("Неуникальное значение");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("Запись уже существует");
        break;
    }

    switch(error.type())
    {
    case QSqlError::NoError:
    case QSqlError::ConnectionError:
        messageBox.setWindowTitle("Ошибка соединения");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Неправильный логин или пароль");
        break;
    case QSqlError::StatementError:
    case QSqlError::TransactionError:
    case QSqlError::UnknownError:
        break;
    }

    qDebug() << "[СООБЩЕНИЕ ОБ ОШИБКИ]: " << error.text();
    messageBox.exec();
}

