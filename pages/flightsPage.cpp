#include "flightsPage.h"
#include "ui_flightsPage.h"
#include "logger.h"
#include "database/database.h"

FlightsPage::FlightsPage(QWidget *parent) :
    Page("рейсы", parent),
    ui(new Ui::FlightsPage)
{
    ui->setupUi(this);
    headers = {"Дата", "Откуда", "Куда", "Самолет", "Цена билета", "Кол-во броней", "Всево билетов", "Статус", "Обновлен"};

    QSqlQueryModel *model = Database::getAllFlights();

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->flightsTableView->setModel(model);
    setupTable(ui->flightsTableView, model, headers);

    connect(ui->flightsTableView, &QTableView::doubleClicked, this, &FlightsPage::openEditAircraftDialog);
    connect(ui->addPushButton, &QPushButton::clicked, this, &FlightsPage::openAddAircraftDialog);
    connect(ui->updatePushButton, &QPushButton::clicked, this, &FlightsPage::update);
}

FlightsPage::~FlightsPage()
{
    delete ui;
    delete editDialog;
}

void FlightsPage::openEditAircraftDialog(const QModelIndex &index)
{
    editDialog = new EditFlightDialog(this, &index);
    connect(editDialog, &EditFlightDialog::modelChanged, this, &FlightsPage::update);
    editDialog->exec();
}

void FlightsPage::openAddAircraftDialog()
{
    editDialog = new EditFlightDialog(this);
    connect(editDialog, &EditFlightDialog::modelChanged, this, &FlightsPage::update);
    editDialog->exec();
}

void FlightsPage::update()
{
    QSqlQueryModel *model = Database::getAllFlights();

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    setupTable(ui->flightsTableView, model, headers);
    ui->flightsTableView->setModel(model);
}
