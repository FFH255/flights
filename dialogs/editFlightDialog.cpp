#include "editFlightDialog.h"
#include "qsqlerror.h"
#include "ui_editFlightDialog.h"
#include "utils.h"
#include "logger.h"

EditFlightDialog::EditFlightDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditFlightDialog)
{
    ui->setupUi(this);
    townTable = new TownTable(this);
    TownsResponse *townsResponse = townTable->selectAll();

    if (townsResponse->error)
    {
        Logger::code(this, *townsResponse->error);
        return;
    }

    for (TownModel* town : *townsResponse->towns)
    {
        ui->fromTownComboBox->addItem(town->name);
        ui->toTownComboBox->addItem(town->name);
    }
    aircraftTable = new AircraftTable(this);
    AvailableModelsResponse *modelsResponse = aircraftTable->selectAvailableModels(QDate::currentDate());

    if (modelsResponse->error)
    {
        Logger::code(this, *modelsResponse->error);
        qDebug() << modelsResponse->error->text();
        return;
    }

    for (const QString &model : *modelsResponse->models)
    {
        ui->aircraftComboBox->addItem(model);
    }

    flightView = new FlightView(this);
    int id = Utils::getIdByIndex(index);
    FlightResponse *flightResponse = flightView->selectById(id);

    if (flightResponse->error)
    {
        Logger::code(this, *flightResponse->error);
        return;
    }
    flightModel = flightResponse->flight;
    ui->dateEdit->setDate(flightModel->date);
    ui->fromTownComboBox->setCurrentText(flightModel->from);
    ui->toTownComboBox->setCurrentText(flightModel->to);
    ui->aircraftComboBox->setCurrentText(flightModel->airplane);
    ui->priceSpinBox->setValue(flightModel->price);

    connect(ui->applyPushButton, &QPushButton::clicked, this, &EditFlightDialog::onApplyPushButtonClicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &EditFlightDialog::onDeletePushButtonClicked);
    connect(ui->ClosePushButton, &QPushButton::clicked, this, &EditFlightDialog::onClosePushButtonClicked);
}

EditFlightDialog::~EditFlightDialog()
{
    delete ui;
    delete townTable;
    delete flightView;
    delete flightModel;
    delete aircraftTable;
}

void EditFlightDialog::onApplyPushButtonClicked()
{
    QDate date = ui->dateEdit->date();
    QString from = ui->fromTownComboBox->currentText();
    QString to = ui->toTownComboBox->currentText();
    QString airplane = ui->aircraftComboBox->currentText();
    int price = ui->priceSpinBox->value();
    qDebug() << date << from << to << airplane << price;

    if (flightModel->date == date &&
        flightModel->from == from &&
        flightModel->to == to &&
        flightModel->airplane == airplane &&
        flightModel->price == price)
    {
        Logger::custom(this, "Change something before applying");
        return;
    }

    if (from == to)
    {
        return;
    }

    Response *res = flightView->update(flightModel->id, date, from, to, airplane, price);

    if (res->error)
    {
        Logger::code(this, *res->error);
        return;
    }
    close();
    emit modelChanged();
}

void EditFlightDialog::onDeletePushButtonClicked()
{

}

void EditFlightDialog::onClosePushButtonClicked()
{
    close();
}
