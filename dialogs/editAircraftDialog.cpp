#include "editAircraftDialog.h"
#include "logger.h"
#include "ui_editAircraftDialog.h"
#include <error.h>
#include <logger.h>
#include "database/database.h"

EditAircraftDialog::EditAircraftDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditAircraftDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Редактирование");
    connect(ui->applyPushButton, &QPushButton::clicked, this, &EditAircraftDialog::onApplyPushButtonClicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &EditAircraftDialog::onDeletePushButtonClicked);
    connect(ui->closePushButton, &QPushButton::clicked, this, &EditAircraftDialog::onClosePushButtonClicked);

    if (!index)
    {
        aircraftOrigin = nullptr;
        ui->deletePushButton->hide();
        return;
    }
    QSqlQueryModel *model = Database::getAircraftByIndex(index);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    aircraftOrigin = new Aircraft(model);
    ui->nameLineEdit->setText(aircraftOrigin->model);
    ui->seatsSpinBox->setValue(aircraftOrigin->seats);
    ui->deletePushButton->show();
}

EditAircraftDialog::~EditAircraftDialog()
{
    delete ui;
    delete aircraftOrigin;

}

void EditAircraftDialog::onApplyPushButtonClicked()
{
    QString name = ui->nameLineEdit->text();
    int seats = ui->seatsSpinBox->text().toInt();

    if(name == "")
    {
        Logger::custom(this, "Введите модель самолета");
        return;
    }
    if(seats <= 0)
    {
        Logger::custom(this, "Количество мест в самолете должно быть больше чем 0");
        return;
    }

    if (!aircraftOrigin)
    {
        QSqlQueryModel *model = Database::addAircraft(name, seats);

        if (model->lastError().isValid())
        {
            Logger::code(this, model->lastError());
            return;
        }
        emit modelChanged();
        close();
        return;
    }

    if (name == aircraftOrigin->model && seats == aircraftOrigin->seats)
    {
        Logger::custom(this, "Измените данные, чтобы сохранить");
        return;
    }

    QSqlQueryModel *model = Database::updateAircraft(aircraftOrigin->id, name, seats);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    emit modelChanged();
    close();
}

void EditAircraftDialog::onDeletePushButtonClicked()
{
    QSqlQueryModel *model = Database::removeAircraft(aircraftOrigin->id);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    emit modelChanged();
    close();
}

void EditAircraftDialog::onClosePushButtonClicked()
{
    this->close();
}
