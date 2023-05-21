
#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class Page: public QWidget
{
    Q_OBJECT

public:
    explicit Page(QString name, QWidget *parent = nullptr);
    QString name;

public slots:
    virtual void render();
    void onShown();

signals:
    void change(QString name);
};

#endif // PAGE_H
