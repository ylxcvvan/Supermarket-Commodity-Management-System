#ifndef WIDGETCASHIERMANAGER_H
#define WIDGETCASHIERMANAGER_H

#include <QWidget>

namespace Ui {
class WidgetCashierManager;
}

class WidgetCashierManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCashierManager(QWidget *parent = nullptr);
    ~WidgetCashierManager();

private:
    Ui::WidgetCashierManager *ui;
};

#endif // WIDGETCASHIERMANAGER_H
