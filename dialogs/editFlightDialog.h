#ifndef EDITFLIGHTDIALOG_H
#define EDITFLIGHTDIALOG_H

#include "database/aircraftTable.h"
#include "database/flightView.h"
#include "database/townTable.h"
#include <QDialog>

namespace Ui {
class EditFlightDialog;
}

class EditFlightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFlightDialog(QWidget *parent = nullptr, const QModelIndex *index = nullptr);
    ~EditFlightDialog();

private:
    Ui::EditFlightDialog *ui;
    TownTable *townTable;
    AircraftTable *aircraftTable;
    FlightView *flightView;
    FlightModel *flightModel;

private slots:
    void onApplyPushButtonClicked();
    void onDeletePushButtonClicked();
    void onClosePushButtonClicked();

signals:
    void modelChanged();
};

#endif // EDITFLIGHTDIALOG_H
