#include "schedulePage.h"
#include "logger.h"
#include "qsqlerror.h"
#include "qsqlrecord.h"
#include "ui_schedulePage.h"
#include "database/database.h"

#include <QDate>

SchedulePage::SchedulePage(QWidget *parent) :
    Page("расписание", parent),
    ui(new Ui::SchedulePage)
{
    ui->setupUi(this);
    setupTownComboBoxes();
    ui->dateEdit->setDate(QDate::currentDate());

    setupSchedule();
    QStringList headers = {"Дата", "Откуда", "Куда"};
    setupTable(ui->scheduleTableView, model, headers);

    connect(ui->searchPushButton, &QPushButton::clicked, this, &SchedulePage::searchSchedule);
    connect(ui->allPushButton, &QPushButton::clicked, this, &SchedulePage::setupSchedule);
    connect(ui->scheduleTableView, &QTableView::doubleClicked, this, &SchedulePage::reserveTicket);
}

SchedulePage::~SchedulePage()
{
    delete ui;
    delete model;
}

void SchedulePage::setupTownComboBoxes()
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

void SchedulePage::searchSchedule()
{
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString from = ui->fromTownComboBox->currentText();
    QString to = ui->toTownComboBox->currentText();
    QSqlQueryModel *model = Database::getFilteredSchedule(date, from, to);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->scheduleTableView->setModel(model);
}

void SchedulePage::setupSchedule()
{
    model = Database::getSchedule();

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->scheduleTableView->setModel(model);
}

void SchedulePage::reserveTicket(const QModelIndex &index)
{
    QSqlQueryModel *model = Database::reserveTicketByIndex(&index);
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    Logger::custom(this, "Success!");
}
