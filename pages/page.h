
#ifndef PAGE_H
#define PAGE_H

#include "qsqlquerymodel.h"
#include "qtableview.h"
#include <QWidget>

class Page: public QWidget
{
    Q_OBJECT

protected:
    void setupTable(QTableView *tableView, QSqlQueryModel *model, QStringList labels);

public:
    explicit Page(QString name, QWidget *parent = nullptr);
    QString name;

public slots:
    void onShown();

signals:
    void change(QString name);
};

#endif // PAGE_H
