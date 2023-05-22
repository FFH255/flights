#include "edittowndialog.h"
#include "qabstractitemmodel.h"
#include "ui_edittowndialog.h"
#include "utils.h"
#include "logger.h"

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
        Logger::code(this, *res->error);
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
        Logger::custom(this, "Please enter town's name", "Town's name is empty string");
        return;
    }

    if (country == "")
    {
        Logger::custom(this, "Please enter country's name", "Country's name is empty string");
        return;
    }

    if (townModel == nullptr)
    {
        Response *res = townTable->insert(name, country);
        if (res->error)
        {
            Logger::code(this, *res->error);
            return;
        }
        emit modelChanged();
        this->close();
        return;
    }
    Response *res = townTable->updateById(townModel->id, name, country);

    if (res->error)
    {
        Logger::code(this, *res->error);
        return;
    }

    if (townModel->name == name && townModel->country == country)
    {
        Logger::custom(this, "Change something before applying");
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
        Logger::code(this, *res->error);
        return;
    }
    emit modelChanged();
    this->close();
}

void EditTownDialog::onClosePushButtonClicked()
{
    this->close();
}



