#ifndef EDITTOWNDIALOG_H
#define EDITTOWNDIALOG_H

#include "database/models/town.h"
#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class EditTownDialog;
}

class EditTownDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::EditTownDialog *ui;
    Town *townOrigin;

public:
    explicit EditTownDialog(QWidget *parent = nullptr, const QModelIndex *index = nullptr);
    ~EditTownDialog();

private slots:
    void onApplyPushButtonClicked();
    void onDeletePushButtonClicked();
    void onClosePushButtonClicked();

signals:
    void modelChanged();
};

#endif // EDITTOWNDIALOG_H
