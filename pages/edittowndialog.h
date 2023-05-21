#ifndef EDITTOWNDIALOG_H
#define EDITTOWNDIALOG_H

#include <QDialog>

namespace Ui {
class EditTownDialog;
}

class EditTownDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTownDialog(QWidget *parent = nullptr);
    ~EditTownDialog();

private:
    Ui::EditTownDialog *ui;
};

#endif // EDITTOWNDIALOG_H
