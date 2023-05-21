#include "aircraftPage.h"
#include "ui_aircraftPage.h"
#include <QMessageBox>

AircraftPage::AircraftPage(QWidget *parent) :
    Page("aircrafts", parent),
    ui(new Ui::AircraftPage)
{
    ui->setupUi(this);
    aircraftTable = new AircraftTable(this);

    ModelResponse res = aircraftTable->getModel();
    if (!res.ok)
    {
        QMessageBox::critical(this, tr("Error"), tr("Something went wrong."));
        qDebug() << res.errorMessage;
        return;
    }

    ui->aircraftTableView->setModel(res.model);
    ui->aircraftTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->aircraftTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->aircraftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->aircraftTableView->hideColumn(0);

    connect(ui->aircraftTableView, &QTableView::doubleClicked, this, &AircraftPage::openEditAircraftDialog);
    connect(ui->addPushButton, &QPushButton::clicked, this, &AircraftPage::openAddAircraftDialog);
}

AircraftPage::~AircraftPage()
{
    delete ui;
    delete aircraftTable;
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
    ModelResponse res = aircraftTable->getModel();
    if (!res.ok)
    {
        QMessageBox::critical(this, tr("Error"), tr("Something went wrong."));
        qDebug() << res.errorMessage;
        return;
    }

    ui->aircraftTableView->setModel(res.model);
}
