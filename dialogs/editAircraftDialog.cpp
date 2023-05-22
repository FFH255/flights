#include "editAircraftDialog.h"
#include "logger.h"
#include "ui_editAircraftDialog.h"
#include "utils.h"

#include <error.h>
#include <logger.h>

EditAircraftDialog::EditAircraftDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditAircraftDialog)
{
    ui->setupUi(this);

    if (index == nullptr)
    {
        originAircraft = nullptr;
    } else
    {
        aircraftTable = new AircraftTable(this);
        int id = Utils::getIdByIndex(index);
        AircraftResponse *res = aircraftTable->selectById(id);

        if (res->error)
        {
            Logger::code(this, *res->error);
            return;
        }

        originAircraft = res->aircraft;
        ui->nameLineEdit->setText(originAircraft->model);
        ui->seatsSpinBox->setValue(originAircraft->seats);
    }

    connect(ui->applyPushButton, &QPushButton::clicked, this, &EditAircraftDialog::onApplyPushButtonClicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &EditAircraftDialog::onDeletePushButtonClicked);
    connect(ui->closePushButton, &QPushButton::clicked, this, &EditAircraftDialog::onClosePushButtonClicked);
}

EditAircraftDialog::~EditAircraftDialog()
{
    delete ui;
    delete aircraftTable;
    delete originAircraft;
}

void EditAircraftDialog::onApplyPushButtonClicked()
{
    QString name = ui->nameLineEdit->text();
    int seats = ui->seatsSpinBox->text().toInt();

    if(name == "")
    {
        Logger::custom(this, "Please, enter towns's");
        return;
    }
    if(seats <= 0)
    {
        Logger::custom(this, "Number of seats should be greated then zero.");
        return;
    }

    if (originAircraft == nullptr)
    {
        Response *res = aircraftTable->insert(name, seats);

        if (res->error)
        {
            Logger::code(this, *res->error);
            return;
        }

        emit modelChanged();
        close();
        return;
    }

    if (name == originAircraft->model && seats == originAircraft->seats)
    {
        Logger::custom(this, "Chage something before applying.");
        return;
    }
    Response *res = aircraftTable->updateById(originAircraft->id, name, seats);

    if (res->error)
    {
        //handle error
        return;
    }
    emit modelChanged();
    close();
}

void EditAircraftDialog::onDeletePushButtonClicked()
{
    Response *res = aircraftTable->deteleById(originAircraft->id);

    if (res->error)
    {
        Logger::code(this, *res->error);
        return;
    }
    emit modelChanged();
    close();
}

void EditAircraftDialog::onClosePushButtonClicked()
{
    this->close();
}
