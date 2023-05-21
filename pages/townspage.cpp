#include "townspage.h"
#include "ui_townspage.h"
#include <QMessageBox>
#include <QSqlTableModel>

TownsPage::TownsPage(QWidget *parent) :
    Page("towns", parent),
    ui(new Ui::TownsPage)
{
    ui->setupUi(this);

    townTable = new TownTable(this);

    ModelResponse *res = townTable->getModel();

    if (res->error)
    {
        //handle error
        return;
    }
    model = res->model;
    this->createUI();
}

TownsPage::~TownsPage()
{
    delete ui;
    delete townTable;
    delete model;
}

void TownsPage::createUI()
{
    ui->townsTableView->setModel(model);
    ui->townsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    ModelResponse *res = townTable->getModel();

    if (res->error)
    {
        //handle error
        return;
    }

    model = res->model;
    ui->townsTableView->setModel(model);
}




