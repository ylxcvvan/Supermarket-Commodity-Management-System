#ifndef WIDGETINVENTORYMANAGER_H
#define WIDGETINVENTORYMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "controller/services/inventorytableservice.h".h"
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
