#ifndef SCHEDULEPAGE_H
#define SCHEDULEPAGE_H

#include "pages/page.h"
#include <QWidget>

namespace Ui {
class SchedulePage;
}

class SchedulePage : public Page
{
    Q_OBJECT

public:
    explicit SchedulePage(QWidget *parent = nullptr);
    ~SchedulePage();

private:
    Ui::SchedulePage *ui;
    QSqlQueryModel *model;
    QStringList headers;
    void setupTownComboBoxes();

private slots:
    void searchSchedule();
    void setupSchedule();
    void reserveTicket(const QModelIndex &index);
};

#endif // SCHEDULEPAGE_H
