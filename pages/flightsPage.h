#ifndef FLIGHTSPAGE_H
#define FLIGHTSPAGE_H

#include <pages/page.h>
#include <QWidget>

namespace Ui {
class FlightsPage;
}

class FlightsPage : public Page
{
    Q_OBJECT

public:
    explicit FlightsPage(QWidget *parent = nullptr);
    ~FlightsPage();

private:
    Ui::FlightsPage *ui;
};

#endif // FLIGHTSPAGE_H
