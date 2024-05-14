#include "widgetcashiermanager.h"
#include "ui_widgetcashiermanager.h"

WidgetCashierManager::WidgetCashierManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCashierManager)
    ,m_GoodsListService(new GoodsListService)
    ,m_ModelGoodsList(m_GoodsListService->getGlist())
{
    ui->setupUi(this);

    // 创建 QTableView
    ui->tableView->setModel(m_ModelGoodsList);



}

WidgetCashierManager::~WidgetCashierManager()
{
    delete ui;
}
