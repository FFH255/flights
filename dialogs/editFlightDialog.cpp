#include "editFlightDialog.h"
#include "qsqlerror.h"
#include "qsqlrecord.h"
#include "ui_editFlightDialog.h"
#include "logger.h"
#include "database/database.h"

EditFlightDialog::EditFlightDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditFlightDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Редактирование");

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
        flightOrigin = nullptr;
        return;
    }

    QSqlQueryModel *model = Database::getFlightByIndex(index);
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }

    flightOrigin = new Flight(model);

    ui->deletePushButton->show();
    ui->dateEdit->setDate(QDate::fromString(flightOrigin->date, "yyyy-MM-dd"));
    ui->fromTownComboBox->setCurrentText(flightOrigin->from);
    ui->toTownComboBox->setCurrentText(flightOrigin->to);

    int i = ui->aircraftComboBox->findText(flightOrigin->airplane);
    if (i == -1)
    {
        ui->aircraftComboBox->addItem(flightOrigin->airplane);
    }
    ui->aircraftComboBox->setCurrentText(flightOrigin->airplane);
    ui->priceSpinBox->setValue(flightOrigin->price);
}

EditFlightDialog::~EditFlightDialog()
{
    delete ui;
    delete flightOrigin;
}

void EditFlightDialog::setupAirplaneComboBox()
{
    ui->aircraftComboBox->clear();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QSqlQueryModel *model = Database::getAvailableModels(date);
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->aircraftComboBox->setModel(model);
}

void EditFlightDialog::setupTownsComboBox()
{
    QSqlQueryModel *model = Database::getAllTowns();

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }

    for(int i = 0; i < model->rowCount(); i++)
    {
        QString name = model->record(i).value("name").toString();
        ui->fromTownComboBox->addItem(name);
        ui->toTownComboBox->addItem(name);

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
        Logger::custom(this, "Город отправления и город назначения не могут быть одинаковыми");
        return;
    }

    if (!flightOrigin)
    {
        QSqlQueryModel *model = Database::addFlight(date, from, to, airplane, price);

        if (model->lastError().isValid())
        {
            Logger::code(this, model->lastError());
            return;
        }
        emit modelChanged();
        close();
        return;
    }

    if (flightOrigin->date == date &&
        flightOrigin->from == from &&
        flightOrigin->to == to &&
        flightOrigin->airplane == airplane &&
        flightOrigin->price == price)
    {
        Logger::custom(this, "Измените данные, чтобы сохранить");
        return;
    }

    QSqlQueryModel *model = Database::updateFlight(flightOrigin->id, date, from, to, airplane, price);
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    close();
    emit modelChanged();
}

void EditFlightDialog::onDeletePushButtonClicked()
{
    QSqlQueryModel *model = Database::removeFlight(flightOrigin->id);
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    emit modelChanged();
    close();
}

void EditFlightDialog::onClosePushButtonClicked()
{
    close();
}
