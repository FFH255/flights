#include "homepage.h"
#include "dialogs/editscheduledialog.h"
#include "ui_homepage.h"
#include "pages/page.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDate>
#include <QDebug>

HomePage::HomePage(QWidget *parent) :
    Page("home", parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_tableView_doubleClicked(const QModelIndex &index)
{
    editDialog->mapper->setCurrentModelIndex(index);
    editDialog->exec();
}

