#include "ticketspage.h"
#include "ui_ticketspage.h"
#include "pages/page.h"

TicketsPage::TicketsPage(QWidget *parent) :
    Page("tickets", parent),
    ui(new Ui::TicketsPage)
{
    ui->setupUi(this);
}

TicketsPage::~TicketsPage()
{
    delete ui;
}
