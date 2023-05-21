#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "page.h"
#include <QSqlQueryModel>
#include "dialogs/editscheduledialog.h"

namespace Ui {
class HomePage;
}

class HomePage : public Page
{
    Q_OBJECT

private:
    EditScheduleDialog *editDialog;

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
