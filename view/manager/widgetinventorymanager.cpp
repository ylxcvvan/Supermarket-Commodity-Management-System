#include "widgetinventorymanager.h"
#include "ui_widgetinventorymanager.h"

WidgetInventoryManager::WidgetInventoryManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetInventoryManager)
    ,p_InventoryTableService(new InventoryTableService)
{
    ui->setupUi(this);

    //设置表样式
    ui->tableView->setCornerButtonEnabled(false);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 设置表头为可变长度，并且拉伸填满表格

    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

}
WidgetInventoryManager::~WidgetInventoryManager()
{
    delete ui;
}

void WidgetInventoryManager::loadModel()
{
    //设置当前模型
    p_InventoryTableService->setITableArray(SqlInventory::QueryInventory());
    ui->tableView->setModel(p_InventoryTableService->getITable());
    for (int i = 0; i < ui->tableView->horizontalHeader()->count(); ++i) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

    // 设置商品描述的表头为自适应内容长度，确保内容完全展现
    ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
}

void WidgetInventoryManager::sortByColumn(int column)
{
    //排序函数
    //TODO
    int sortedColumn = ui->tableView->horizontalHeader()->sortIndicatorSection();
    Qt::SortOrder order = ui->tableView->horizontalHeader()->sortIndicatorOrder();

    // 如果 sortedColumn 为 -1，表示没有按照任何表头排序
    if (sortedColumn != -1) {
        qDebug() << "当前按照第" << sortedColumn << "列排序，排序顺序为" << (order == Qt::AscendingOrder ? "升序" : "降序");
    } else {
        qDebug() << "当前没有按照任何表头排序";
    }

    p_InventoryTableService->sortByColumn(column,order);

}




void WidgetInventoryManager::on_pushButtonSelect_clicked()
{

}

