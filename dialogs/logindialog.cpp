#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
    , db("QPSQL")
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_submit, &QPushButton::clicked, this, &LoginDialog::onSubmited);
}

LoginDialog::~LoginDialog()
{
    delete ui;
    db.disconnect();
}

void LoginDialog::onSubmited()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    bool ok = db.connect(
        "localhost",
        5433,
        "flights",
        username,
        password);

    if (!ok)
    {
        QMessageBox::critical(this, tr("Error"), tr("Error connecting to database."));
    } else
    {
        emit loggedIn();
        close();
    }
}
