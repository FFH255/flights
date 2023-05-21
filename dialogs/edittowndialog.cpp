#include "edittowndialog.h"
#include "qabstractitemmodel.h"
#include "ui_edittowndialog.h"
#include "utils.h"
#include <QMessageBox>

EditTownDialog::EditTownDialog(QWidget *parent, const QModelIndex *index) :
    QDialog(parent),
    ui(new Ui::EditTownDialog)
{
    ui->setupUi(this);

    townTable = new TownTable(this);

    connect(ui->applyPushButton, &QPushButton::clicked, this, &EditTownDialog::onApplyPushButtonClicked);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &EditTownDialog::onDeletePushButtonClicked);
    connect(ui->closePushButton, &QPushButton::clicked, this, &EditTownDialog::onClosePushButtonClicked);

    if (index == nullptr)
    {
        ui->deletePushButton->hide();
        townModel = nullptr;
    } else
    {
        int id = Utils::getIdByIndex(index);
        setCurrent(id);
    }
}

EditTownDialog::~EditTownDialog()
{
    delete ui;
    delete townTable;
    delete townModel;
}

void EditTownDialog::setCurrent(int id)
{
    TownResponse *res = townTable->selectById(id);

    if (res->error)
    {
        //handle error
        return;
    }

    townModel = res->town;
    ui->townLineEdit->setText(townModel->name);
    ui->countryLineEdit->setText(townModel->country);
}

void EditTownDialog::onApplyPushButtonClicked()
{
    QString name = ui->townLineEdit->text();
    QString country = ui->countryLineEdit->text();

    if (name == "")
    {
        QMessageBox::information(this, tr("Missing info"), tr("Please enter town's name."));
        return;
    }

    if (country == "")
    {
        QMessageBox::information(this, tr("Missing info"), tr("Please enter country's name."));
        return;
    }

    if (townModel == nullptr)
    {
        Response *res = townTable->insert(name, country);
        if (res->error)
        {
            //handle error
            return;
        }
        emit modelChanged();
        this->close();
        return;
    }
    Response *res = townTable->updateById(townModel->id, name, country);

    if (res->error)
    {
        //handle error
        return;
    }

    if (townModel->name == name && townModel->country == country)
    {
        QMessageBox::information(this, tr("Change something."), tr("Some fields are the same."));
        return;
    }

    emit modelChanged();
    this->close();
}

void EditTownDialog::onDeletePushButtonClicked()
{
    Response *res = townTable->deteleById(townModel->id);

    if (res->error)
    {
        //handle error
        return;
    }
    emit modelChanged();
    this->close();
}

void EditTownDialog::onClosePushButtonClicked()
{
    this->close();
}



