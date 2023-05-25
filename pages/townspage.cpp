#include "townspage.h"
#include "ui_townspage.h"
#include "logger.h"
#include <QSqlTableModel>
#include <qheaderview.h>
#include "database/database.h"

TownsPage::TownsPage(QWidget *parent) :
    Page("города", parent),
    ui(new Ui::TownsPage)
{
    ui->setupUi(this);
    headers = {"Название", "Страна"};
    QSqlQueryModel *model = Database::getAllTowns();
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    this->model = model;
    ui->townsTableView->setModel(model);
    setupTable(ui->townsTableView, model, headers);

    connect(ui->townsTableView, &QTableView::doubleClicked, this, &TownsPage::openEditTownDialog);
    connect(ui->addNewTownPushButton, &QPushButton::clicked, this, &TownsPage::openAddTownDialog);
    connect(ui->updatePushButton, &QPushButton::clicked, this, &TownsPage::update);
}

TownsPage::~TownsPage()
{
    delete ui;
    delete model;
}

void TownsPage::openEditTownDialog(const QModelIndex &index)
{
    editDialog = new EditTownDialog(this, &index);
    connect(editDialog, &EditTownDialog::modelChanged, this, &TownsPage::update);
    editDialog->exec();
}

void TownsPage::openAddTownDialog()
{
    editDialog = new EditTownDialog(this);
    connect(editDialog, &EditTownDialog::modelChanged, this, &TownsPage::update);
    editDialog->exec();
}

void TownsPage::update()
{
    QSqlQueryModel *model = Database::getAllTowns();
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    setupTable(ui->townsTableView, model, headers);
    this->model = model;
    ui->townsTableView->setModel(model);
}




