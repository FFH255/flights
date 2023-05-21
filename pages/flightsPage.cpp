#include "flightsPage.h"
#include "ui_flightsPage.h"

FlightsPage::FlightsPage(QWidget *parent) :
    Page("flights", parent),
    ui(new Ui::FlightsPage)
{
    ui->setupUi(this);
}

FlightsPage::~FlightsPage()
{
    delete ui;
}
