#ifndef EDITTOWNDIALOG_H
#define EDITTOWNDIALOG_H

#include "database/townTable.h"
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
    TownTable *townTable;
    TownModel *townModel;

public:
    explicit EditTownDialog(QWidget *parent = nullptr, const QModelIndex *index = nullptr);
    ~EditTownDialog();

private:
    void setCurrent(int id);

private slots:
    void onApplyPushButtonClicked();
    void onDeletePushButtonClicked();
    void onClosePushButtonClicked();

signals:
    void modelChanged();
};

#endif // EDITTOWNDIALOG_H
