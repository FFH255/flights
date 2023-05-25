
#include "page.h"
#include "qheaderview.h"
#include <QStringListModel>
#include <QWidget>

Page::Page(QString name, QWidget *parent) : QWidget(parent)
{
    this->name = name;
}

void Page::setupTable(QTableView *tableView, QSqlQueryModel *model, QStringList labels)
{
    for (int i = 0; i < labels.count(); i++)
    {
        model->setHeaderData(i+1, Qt::Horizontal, labels.at(i));
    }
    tableView->hideColumn(0);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Page::onShown()
{
    emit change(name);
}

