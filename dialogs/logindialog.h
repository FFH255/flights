#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "database/database.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    Database db;

private:
    Ui::LoginDialog *ui;

private slots:
    void onSubmited();

signals:
    void loggedIn();
};

#endif // LOGINDIALOG_H
