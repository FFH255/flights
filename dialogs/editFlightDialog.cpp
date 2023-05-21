#include "editFlightDialog.h"
#include "qsqlerror.h"
#include "ui_editFlightDialog.h"
#include "utils.h"

EditFlightDialog::EditFlightDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditFlightDialog)
{
    ui->setupUi(this);
    townTable = new TownTable(this);
    TownsResponse *townsResponse = townTable->selectAll();

    if (townsResponse->error)
    {
        //handle error
        return;
    }
    for (TownModel* town : *townsResponse->towns)
    {
        ui->fromTownComboBox->addItem(town->name);
        ui->toTownComboBox->addItem(town->name);
    }
    flightView = new FlightView(this);
    int id = Utils::getIdByIndex(index);
    FlightResponse *flightResponse = flightView->selectById(id);

    if (flightResponse->error)
    {
        qDebug() << flightResponse->error->text();
        return;
    }
    flightModel = flightResponse->flight;
    ui->dateEdit->setDate(flightModel->date);
    ui->fromTownComboBox->setCurrentText(flightModel->from);
    ui->toTownComboBox->setCurrentText(flightModel->to);
    qDebug() << flightModel->price;
    ui->priceSpinBox->setValue(flightModel->price);
}

EditFlightDialog::~EditFlightDialog()
{
    delete ui;
    delete townTable;
    delete flightView;
    delete flightModel;
}

void EditFlightDialog::onApplyPushButtonClicked()
{

}

void EditFlightDialog::onDeletePushButtonClicked()
{

}

void EditFlightDialog::onClosePushButtonClicked()
{

}
