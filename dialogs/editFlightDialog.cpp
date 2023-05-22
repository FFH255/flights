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
    aircraftTable = new AircraftTable(this);
    flightView = new FlightView(this);

    setupTownsComboBox();
    setupAirplaneComboBox();

    connect(ui->applyPushButton, &QPushButton::clicked, this, &EditFlightDialog::onApplyPushButtonClicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &EditFlightDialog::onDeletePushButtonClicked);
    connect(ui->ClosePushButton, &QPushButton::clicked, this, &EditFlightDialog::onClosePushButtonClicked);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &EditFlightDialog::setupAirplaneComboBox);

    if (!index)
    {
        ui->deletePushButton->hide();
        ui->dateEdit->setDate(QDate::currentDate());
        flightModel = nullptr;
        return;
    }

    int id = Utils::getIdByIndex(index);
    FlightResponse *flightResponse = flightView->selectById(id);

    if (flightResponse->error)
    {
        Logger::code(this, *flightResponse->error);
        return;
    }

    flightModel = flightResponse->flight;

    ui->deletePushButton->show();

    ui->dateEdit->setDate(QDate::fromString(flightModel->date, "yyyy-MM-dd"));
    ui->fromTownComboBox->setCurrentText(flightModel->from);
    ui->toTownComboBox->setCurrentText(flightModel->to);

    int i = ui->aircraftComboBox->findText(flightModel->airplane);
    if (i == -1)
    {
        ui->aircraftComboBox->addItem(flightModel->airplane);
    }
    ui->aircraftComboBox->setCurrentText(flightModel->airplane);

    ui->priceSpinBox->setValue(flightModel->price);
}

EditFlightDialog::~EditFlightDialog()
{
    delete ui;
    delete townTable;
    delete flightView;
    delete flightModel;
    delete aircraftTable;
}

void EditFlightDialog::setupAirplaneComboBox()
{
    ui->aircraftComboBox->clear();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    AvailableModelsResponse *modelsResponse = aircraftTable->selectAvailableModels(date);

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
}

void EditFlightDialog::setupTownsComboBox()
{
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
}

void EditFlightDialog::onApplyPushButtonClicked()
{
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString from = ui->fromTownComboBox->currentText();
    QString to = ui->toTownComboBox->currentText();
    QString airplane = ui->aircraftComboBox->currentText();
    int price = ui->priceSpinBox->value();

    if (from == to)
    {
        Logger::custom(this, "The destination city and the departure city cannot be the same");
        return;
    }

    if (!flightModel)
    {
        Response *res = flightView->insert(date, from, to, airplane, price);

        if (res->error)
        {
            Logger::code(this, *res->error);
            return;
        }
        emit modelChanged();
        close();
        return;
    }

    if (flightModel->date == date &&
        flightModel->from == from &&
        flightModel->to == to &&
        flightModel->airplane == airplane &&
        flightModel->price == price)
    {
        Logger::custom(this, "Change something before applying");
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
    Response *res = flightView->deleteById(flightModel->id);

    if (res->error)
    {
        Logger::code(this, *res->error);
        return;
    }
    emit modelChanged();
    close();
}

void EditFlightDialog::onClosePushButtonClicked()
{
    close();
}
