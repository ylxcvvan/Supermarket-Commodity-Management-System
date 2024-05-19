#ifndef WIDGETCASHIERMANAGER_H
#define WIDGETCASHIERMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "controller/services/goodstableservice.h"
#include"controller/services/comitemtableservice.h"
#include"controller/database/sqlcommondityitem.h"
namespace Ui {
class WidgetCashierManager;
}

class WidgetCashierManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCashierManager(QWidget *parent = nullptr);
    ~WidgetCashierManager();
    void loadModel();
private:
    void findAllTableViews(QObject *parent, QVector<QTableView*> &viewList);


private:
    Ui::WidgetCashierManager *ui;
    GoodsTableService *p_GoodsListService;
    ComItemTableService *p_ComItemService;

};

#endif // WIDGETCASHIERMANAGER_H
