#include "flightsPage.h"
#include "ui_flightsPage.h"
#include "logger.h"

FlightsPage::FlightsPage(QWidget *parent) :
    Page("flights", parent),
    ui(new Ui::FlightsPage)
{
    ui->setupUi(this);
    flightView = new FlightView(this);
    ModelResponse *res = flightView->getModel();

    if (res->error)
    {
        Logger::code(this, *res->error);
        return;
    }
    ui->flightsTableView->setModel(res->model);
    ui->flightsTableView->setModel(res->model);
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
    delete flightView;
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
    ModelResponse *res = flightView->getModel();

    if (res->error)
    {
        Logger::code(this, *res->error);
        return;
    }
    ui->flightsTableView->setModel(res->model);
}
