#ifndef AIRCRAFTPAGE_H
#define AIRCRAFTPAGE_H

#include "database/models/aircraft.h"
#include "dialogs/editAircraftDialog.h"
#include "pages/page.h"
#include <QWidget>

namespace Ui {
class AircraftPage;
}

class AircraftPage : public Page
{
    Q_OBJECT

public:
    explicit AircraftPage(QWidget *parent = nullptr);
    ~AircraftPage();

private:
    Ui::AircraftPage *ui;
    EditAircraftDialog *editDialog;

private slots:
    void openEditAircraftDialog(const QModelIndex &index);
    void openAddAircraftDialog();
    void update();
};

#endif // AIRCRAFTPAGE_H
