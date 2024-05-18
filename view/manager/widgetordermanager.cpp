#include "widgetordermanager.h"
#include "ui_widgetordermanager.h"

WidgetOrderManager::WidgetOrderManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetOrderManager)
    ,p_OrderTableService(new OrderTableService)
{
    ui->setupUi(this);

    //设置表的样式
    ui->tableView->setCornerButtonEnabled(false);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

WidgetOrderManager::~WidgetOrderManager()
{
    delete p_OrderTableService;
    delete ui;
}

void WidgetOrderManager::loadModel()
{

}
