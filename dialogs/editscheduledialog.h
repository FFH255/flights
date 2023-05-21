#ifndef EDITSCHEDULEDIALOG_H
#define EDITSCHEDULEDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class EditScheduleDialog;
}

class EditScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditScheduleDialog(QWidget *parent = nullptr);
    ~EditScheduleDialog();
    QDataWidgetMapper *mapper;
    void setModel(QAbstractItemModel* model);

private slots:
    void on_pushButton_apply_clicked();
    void on_pushButton_close_clicked();

private:
    Ui::EditScheduleDialog *ui;
};

#endif // EDITSCHEDULEDIALOG_H
