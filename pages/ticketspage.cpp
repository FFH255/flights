#include "ticketspage.h"
#include "qsqlerror.h"
#include "qsqlquerymodel.h"
#include "ui_ticketspage.h"
#include "pages/page.h"
#include "database/database.h"
#include "logger.h"

TicketsPage::TicketsPage(QWidget *parent) :
    Page("билеты", parent),
    ui(new Ui::TicketsPage)
{
    ui->setupUi(this);
    headers = {"Дата вылета", "Откуда", "Куда", "Цена", "Дата бронирования"};
    update();
    connect(ui->ticketsTableView, &QTableView::doubleClicked, this, &TicketsPage::refundTicket);
    connect(ui->updatePushButton, &QPushButton::clicked, this, &TicketsPage::update);
}

TicketsPage::~TicketsPage()
{
    delete ui;
    delete model;
}

void TicketsPage::update()
{
    model = Database::getAllTickets();

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    setupTable(ui->ticketsTableView, model, headers);
    ui->ticketsTableView->setModel(model);
}

void TicketsPage::refundTicket(const QModelIndex &index)
{
    QSqlQueryModel *model = Database::refundTicketByIndex(&index);

    if (model->lastError().isValid())
    {
        Logger::code(this, model->lastError());
        return;
    }
    Logger::custom(this, "Ticket is refuned!");
    update();
}
