#include "widgetcashiermanager.h"
#include "ui_widgetcashiermanager.h"

WidgetCashierManager::WidgetCashierManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCashierManager)
    ,p_GoodsListService(new GoodsListService)
{
    ui->setupUi(this);

    // 创建 QTableView
    ui->tableView->setModel(p_GoodsListService->getGlist());



}

WidgetCashierManager::~WidgetCashierManager()
{
    delete ui;
}
