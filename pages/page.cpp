
#include "page.h"
#include <QWidget>

Page::Page(QString name, QWidget *parent) : QWidget(parent)
{
    this->name = name;
}

void Page::render()
{

}

void Page::onShown()
{
    emit change(name);
}

