#ifndef WIDGETCASHIERMANAGER_H
#define WIDGETCASHIERMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "controller/services/goodstableservice.h"
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
    GoodsTableService *p_GoodsListService;

};

#endif // WIDGETCASHIERMANAGER_H
