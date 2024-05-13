#include "widgetcashiermanager.h"
#include "ui_widgetcashiermanager.h"

WidgetCashierManager::WidgetCashierManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCashierManager)
{
    ui->setupUi(this);


    // 创建 QStandardItemModel
    cashier_standard_model = new QStandardItemModel();
    cashier_standard_model->setColumnCount(4);
    cashier_standard_model->setHorizontalHeaderLabels({"商品名称","价格","数量","总价"});

    // 创建 QTableView
    cashier_table_view = ui->tableView;
    ui->tableView->setModel(cashier_standard_model);


}

WidgetCashierManager::~WidgetCashierManager()
{
    delete ui;
}
