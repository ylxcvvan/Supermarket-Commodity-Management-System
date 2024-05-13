#ifndef WIDGETINVENTORYMANAGER_H
#define WIDGETINVENTORYMANAGER_H

#include <QWidget>

namespace Ui {
class WidgetInventoryManager;
}

class WidgetInventoryManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetInventoryManager(QWidget *parent = nullptr);
    ~WidgetInventoryManager();

private:
    Ui::WidgetInventoryManager *ui;
};

#endif // WIDGETINVENTORYMANAGER_H
