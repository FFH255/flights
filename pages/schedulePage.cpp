#include "schedulePage.h"
#include "ui_schedulePage.h"

SchedulePage::SchedulePage(QWidget *parent) :
    Page("schedule", parent),
    ui(new Ui::SchedulePage)
{
    ui->setupUi(this);
}

SchedulePage::~SchedulePage()
{
    delete ui;
}
