#ifndef TICKETSPAGE_H
#define TICKETSPAGE_H

#include "pages/page.h"
#include <QWidget>

namespace Ui {
class TicketsPage;
}

class TicketsPage : public Page
{
    Q_OBJECT

public:
    explicit TicketsPage(QWidget *parent = nullptr);
    ~TicketsPage();

private:
    Ui::TicketsPage *ui;
    QSqlQueryModel *model;
    QStringList headers;

private slots:
    void refundTicket(const QModelIndex &index);
    void update();

};

#endif // TICKETSPAGE_H
