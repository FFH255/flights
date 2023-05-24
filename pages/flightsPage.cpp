#include "flightsPage.h"
#include "ui_flightsPage.h"
#include "logger.h"
#include "database/database.h"

FlightsPage::FlightsPage(QWidget *parent) :
    Page("flights", parent),
    ui(new Ui::FlightsPage)
{
    ui->setupUi(this);
    QSqlQueryModel *model = Database::getAllFlights();
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->flightsTableView->setModel(model);
    ui->flightsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->flightsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->flightsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->flightsTableView->hideColumn(0);

    connect(ui->flightsTableView, &QTableView::doubleClicked, this, &FlightsPage::openEditAircraftDialog);
    connect(ui->addPushButton, &QPushButton::clicked, this, &FlightsPage::openAddAircraftDialog);
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
    ui->flightsTableView->setModel(model);
}
