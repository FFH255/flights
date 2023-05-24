#ifndef FLIGHTSPAGE_H
#define FLIGHTSPAGE_H

#include "dialogs/editFlightDialog.h"
#include <pages/page.h>
#include <QWidget>

namespace Ui {
class FlightsPage;
}

class FlightsPage : public Page
{
    Q_OBJECT

private:
    EditFlightDialog *editDialog;

public:
    explicit FlightsPage(QWidget *parent = nullptr);
    ~FlightsPage();

private:
    Ui::FlightsPage *ui;

private slots:
    void openEditAircraftDialog(const QModelIndex &index);
    void openAddAircraftDialog();
    void update();
};

#endif // FLIGHTSPAGE_H
