#include "townspage.h"
#include "ui_townspage.h"
#include "logger.h"
#include <QSqlTableModel>
#include "database/database.h"

TownsPage::TownsPage(QWidget *parent) :
    Page("towns", parent),
    ui(new Ui::TownsPage)
{
    ui->setupUi(this);
    QSqlQueryModel *model = Database::getAllTowns();
    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    this->model = model;
    this->createUI();
}

TownsPage::~TownsPage()
{
    delete ui;
    delete model;
}

void TownsPage::createUI()
{
    ui->townsTableView->setModel(model);
    ui->townsTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->townsTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->townsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->townsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->townsTableView->hideColumn(0);

    connect(ui->townsTableView, &QTableView::doubleClicked, this, &TownsPage::openEditTownDialog);
    connect(ui->addNewTownPushButton, &QPushButton::clicked, this, &TownsPage::openAddTownDialog);
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
    this->model = model;
    ui->townsTableView->setModel(model);
}




