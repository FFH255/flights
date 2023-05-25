#include "edittowndialog.h"
#include "qabstractitemmodel.h"
#include "ui_edittowndialog.h"
#include "logger.h"
#include <QSqlField>
#include "database/database.h"

EditTownDialog::EditTownDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditTownDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Редактирование");

    connect(ui->applyPushButton, &QPushButton::clicked, this, &EditTownDialog::onApplyPushButtonClicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &EditTownDialog::onDeletePushButtonClicked);
    connect(ui->closePushButton, &QPushButton::clicked, this, &EditTownDialog::onClosePushButtonClicked);

    if (!index)
    {
        ui->deletePushButton->hide();
        townOrigin = nullptr;
        return;
    }
    QSqlQueryModel *model = Database::getTownByIndex(index);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    this->townOrigin = new Town(model);
    ui->deletePushButton->show();

    ui->townLineEdit->setText(townOrigin->name);
    ui->countryLineEdit->setText(townOrigin->country);
}

EditTownDialog::~EditTownDialog()
{
    delete ui;
    delete townOrigin;
}

void EditTownDialog::onApplyPushButtonClicked()
{
    QString name = ui->townLineEdit->text();
    QString country = ui->countryLineEdit->text();

    if (name == "")
    {
        Logger::custom(this, "Please enter town's name", "Town's name is empty string");
        return;
    }

    if (country == "")
    {
        Logger::custom(this, "Please enter country's name", "Country's name is empty string");
        return;
    }

    if (!townOrigin)
    {
        QSqlQueryModel *model = Database::addTown(name, country);

        if (model->lastError().isValid())
        {
            Logger::code(this, model->lastError());
            return;
        }

        emit modelChanged();
        this->close();
        return;
    }

    if (townOrigin->name == name && townOrigin->country == country)
    {
        Logger::custom(this, "Change something before applying");
        return;
    }
    QSqlQueryModel *model = Database::updateTown(townOrigin->id, name, country);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }

    emit modelChanged();
    this->close();
}

void EditTownDialog::onDeletePushButtonClicked()
{
    QSqlQueryModel *model = Database::removeTown(townOrigin->id);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    emit modelChanged();
    this->close();
}

void EditTownDialog::onClosePushButtonClicked()
{
    this->close();
}



