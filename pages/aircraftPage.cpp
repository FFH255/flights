#include "aircraftPage.h"
#include "ui_aircraftPage.h"
#include "logger.h"
#include "database/database.h"

AircraftPage::AircraftPage(QWidget *parent) :
    Page("aircrafts", parent),
    ui(new Ui::AircraftPage)
{
    ui->setupUi(this);
    QSqlQueryModel *model = Database::getAllAircrafts();

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->aircraftTableView->setModel(model);
    ui->aircraftTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->aircraftTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->aircraftTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->aircraftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->aircraftTableView->hideColumn(0);

    connect(ui->aircraftTableView, &QTableView::doubleClicked, this, &AircraftPage::openEditAircraftDialog);
    connect(ui->addPushButton, &QPushButton::clicked, this, &AircraftPage::openAddAircraftDialog);
}

AircraftPage::~AircraftPage()
{
    delete ui;
    delete editDialog;
}

void AircraftPage::openEditAircraftDialog(const QModelIndex &index)
{
    editDialog = new EditAircraftDialog(this, &index);
    connect(editDialog, &EditAircraftDialog::modelChanged, this, &AircraftPage::update);
    editDialog->exec();
}

void AircraftPage::openAddAircraftDialog()
{
    editDialog = new EditAircraftDialog(this);
    connect(editDialog, &EditAircraftDialog::modelChanged, this, &AircraftPage::update);
    editDialog->exec();
}

void AircraftPage::update()
{
    QSqlQueryModel *model = Database::getAllAircrafts();
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    ui->aircraftTableView->setModel(model);
}
