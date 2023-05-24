#ifndef EDITAIRCRAFTDIALOG_H
#define EDITAIRCRAFTDIALOG_H

#include "database/models/aircraft.h"
#include <QDialog>

namespace Ui {
class EditAircraftDialog;
}

class EditAircraftDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAircraftDialog(QWidget *parent = nullptr, const QModelIndex *index = nullptr);
    ~EditAircraftDialog();

private:
    Ui::EditAircraftDialog *ui;
    Aircraft *aircraftOrigin;

private slots:
    void onApplyPushButtonClicked();
    void onDeletePushButtonClicked();
    void onClosePushButtonClicked();

signals:
    void modelChanged();
};

#endif // EDITAIRCRAFTDIALOG_H
