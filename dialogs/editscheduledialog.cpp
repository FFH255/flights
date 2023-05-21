#include "editscheduledialog.h"
#include "ui_editscheduledialog.h"

EditScheduleDialog::EditScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditScheduleDialog)
{
    ui->setupUi(this);

    mapper = new QDataWidgetMapper(this);
}

EditScheduleDialog::~EditScheduleDialog()
{
    delete ui;
    delete mapper;
}

void EditScheduleDialog::setModel(QAbstractItemModel* model) {
    mapper->setModel(model);

    mapper->addMapping(ui->dateEdit_date, 1);
    mapper->addMapping(ui->comboBox_departure_town, 2);
    mapper->addMapping(ui->comboBox_arrival_town, 3);
    mapper->addMapping(ui->comboBox_airplane, 4);
    mapper->addMapping(ui->spinBox_price, 5);
}

void EditScheduleDialog::on_pushButton_apply_clicked()
{
    mapper->submit();
}


void EditScheduleDialog::on_pushButton_close_clicked()
{
    close();
}

