#include "widgetinventorymanager.h"
#include "ui_widgetinventorymanager.h"

WidgetInventoryManager::WidgetInventoryManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetInventoryManager)
    ,p_InventoryTableService(new InventoryTableService)
{
    ui->setupUi(this);

    p_InventoryTableService->setITableArray(SqlInventory::QueryInventory());
    //设置表样式
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //设置当前模型
    ui->tableView->setModel(p_InventoryTableService->getITable());
}

WidgetInventoryManager::~WidgetInventoryManager()
{
    delete ui;
}




void WidgetInventoryManager::on_pushButtonSelect_clicked()
{

}

