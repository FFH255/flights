#ifndef TOWNSPAGE_H
#define TOWNSPAGE_H

#include "dialogs/edittowndialog.h"
#include "pages/page.h"
#include <QWidget>

namespace Ui {
class TownsPage;
}

class TownsPage : public Page
{
    Q_OBJECT

private:
    Ui::TownsPage *ui;

    QSqlQueryModel *model;
    QStringList headers;
    EditTownDialog *editDialog;

public:
    TownsPage(QWidget *parent = nullptr);
    ~TownsPage();

private slots:
    void openEditTownDialog(const QModelIndex &index);
    void openAddTownDialog();
    void update();
};

#endif // TOWNSPAGE_H
