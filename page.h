
#ifndef PAGE_H
#define PAGE_H

#include <QWidget.h>

class Page : QWidget
{
    Q_OBJECT

public:
    Page();

public slots:
    virtual void init();
};

#endif // PAGE_H
