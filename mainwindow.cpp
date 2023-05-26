
#include "mainwindow.h"
#include "dialogs/logindialog.h"
#include "pages/aircraftPage.h"
#include "pages/flightsPage.h"
#include "pages/schedulePage.h"
#include "pages/ticketspage.h"
#include "pages/townspage.h"
#include "qpushbutton.h"
#include "qsqlrecord.h"
#include "ui_mainwindow.h"
#include "database/database.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LoginDialog loginDialog;
    connect(&loginDialog, &LoginDialog::loggedIn, this, &MainWindow::show);
    loginDialog.exec();

    QSqlQueryModel *model = Database::whoami();
    QString role = model->record(0).value("current_user").toString();

    if (role == "user")
    {
        pages.append(new TicketsPage(this));
        pages.append(new SchedulePage(this));
    }

    if (role == "admin")
    {
        pages.append(new FlightsPage(this));
        pages.append(new TicketsPage(this));
        pages.append(new TownsPage(this));
        pages.append(new AircraftPage(this));
        pages.append(new SchedulePage(this));
    }

    pageController = new QStackedWidget(this);

    for (Page* page : pages)
    {
        pageController->addWidget(page);
        connect(page, &Page::change, this, &MainWindow::onPageChanged);
        QPushButton *button = new QPushButton();
        button->setText(page->name);
        ui->buttonsLayout->addWidget(button);
        connect(button, &QPushButton::clicked, page, &Page::onShown);
    }

    ui->layout_pages->addWidget(pageController);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPageChanged(QString name)
{
    if (pages.size() == 0)
    {
        return;
    }

    for (Page *page : pages)
    {
        if (page->name == name)
        {
            pageController->setCurrentWidget(page);
            return;
        }
    }
}


