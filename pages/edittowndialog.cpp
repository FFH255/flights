#include "edittowndialog.h"
#include "ui_edittowndialog.h"

EditTownDialog::EditTownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTownDialog)
{
    ui->setupUi(this);
}

EditTownDialog::~EditTownDialog()
{
    delete ui;
}
