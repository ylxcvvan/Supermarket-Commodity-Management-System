#ifndef WIDGETORDERMANAGER_H
#define WIDGETORDERMANAGER_H

#include <QWidget>

namespace Ui {
class WidgetOrderManager;
}

class WidgetOrderManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetOrderManager(QWidget *parent = nullptr);
    ~WidgetOrderManager();

private:
    Ui::WidgetOrderManager *ui;
};

#endif // WIDGETORDERMANAGER_H
