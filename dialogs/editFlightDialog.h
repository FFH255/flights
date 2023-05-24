#ifndef EDITFLIGHTDIALOG_H
#define EDITFLIGHTDIALOG_H

#include "database/models/flight.h"
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
    Flight *flightOrigin;

    void setupTownsComboBox();

private slots:
    void onApplyPushButtonClicked();
    void onDeletePushButtonClicked();
    void onClosePushButtonClicked();
    void setupAirplaneComboBox();

signals:
    void modelChanged();
};

#endif // EDITFLIGHTDIALOG_H
