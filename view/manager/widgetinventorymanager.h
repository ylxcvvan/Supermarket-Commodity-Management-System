#ifndef WIDGETINVENTORYMANAGER_H
#define WIDGETINVENTORYMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include"controller/services/inventorytableservice.h"
namespace Ui {
class WidgetInventoryManager;
}

class WidgetInventoryManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetInventoryManager(QWidget *parent = nullptr);
    ~WidgetInventoryManager();
    void loadModel();

private slots:

    void sortByColumn(int column);
    void on_pushButtonSelect_clicked();

private:
    Ui::WidgetInventoryManager *ui;

    InventoryTableService *p_InventoryTableService;
};

#endif // WIDGETINVENTORYMANAGER_H
