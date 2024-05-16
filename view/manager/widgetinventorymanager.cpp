#include "widgetinventorymanager.h"
#include "ui_widgetinventorymanager.h"
#include<QMessageBox>
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

    //设置“商品类别”下拉框
    for(auto &s:p_InventoryTableService->getComboBoxDelegate()->getComBoBoxCategory())
    {
        ui->comboBoxCategory->addItem(s);
    }

    //设置单击表头排序
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    //设置商品类型的comboBox
    ui->tableView->setItemDelegateForColumn(3,p_InventoryTableService->getComboBoxDelegate());

    //设置可以编辑
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    InitBoolSearchState();
    InitLineEditInputMode();

}
WidgetInventoryManager::~WidgetInventoryManager()
{
    delete ui;
}

void WidgetInventoryManager::loadModel()
{
    //进行查询
    int id=SearchInventoryId?ui->lineEditInventoryId->text().toInt():-1;
    int cid=SearchCommodityId?ui->LineEditCommodityId->text().toInt():-1;
    QString cname=SearchName?ui->LineEditCommodityName->text():"";
    QString category=SearchCategory?ui->comboBoxCategory->currentText():"";
    QString details=SearchDetails?ui->lineEditDetails->text():"";
    QDate sellbytime=SearchSellByTime?QDate::fromString(ui->lineEditSellByTime->text(),"yyyy-MM-dd"):QDate();
    if (!sellbytime.isValid()&&SearchSellByTime) {
        // 处理有效的日期
        // 提示用户输入的日期无效
        QMessageBox::warning(this, "Invalid Date", "Please enter a valid date in the format yyyy-MM-dd.");
        // 清空文本框或者设置默认日期
        ui->lineEditSellByTime->clear(); // 清空文本框
        // 或者设置默认日期
        ui->lineEditSellByTime->setText("2099-12-31"); // 设置为当前日期
        return;
    }
    double minprice=SearchPrice?ui->lineEditMinPrice->text().toDouble():-1;
    double maxprice=SearchPrice?ui->lineEditMaxPrice->text().toDouble():1e10;

    double mincostprice=SearchCostPrice?ui->lineEditMinCostPrice->text().toDouble():-1;
    double maxcostprice=SearchCostPrice?ui->lineEditMaxCostPrice->text().toDouble():1e10;

    double minamount=SearchAmount?ui->lineEditMinAmount->text().toDouble():-1;
    double maxamount=SearchAmount?ui->lineEditMaxAmount->text().toDouble():1e10;
    p_InventoryTableService->setITableArray(SqlInventory::Query(id,cid,cname,category,details,sellbytime
                                                                ,minprice,maxprice,mincostprice,maxcostprice
                                                                ,minamount,maxamount));


    //设置当前模型
    ui->tableView->setModel(p_InventoryTableService->getITable());
    ui->tableView->update();
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
    loadModel();
}

void WidgetInventoryManager::on_pushButtonCommodityName_clicked(bool checked)
{
    SearchName=checked;
}

void WidgetInventoryManager::on_pushButtonCommodityId_clicked(bool checked)
{
    SearchCommodityId=checked;
}

void WidgetInventoryManager::on_pushButtonSellByTime_clicked(bool checked)
{
    SearchSellByTime=checked;
}

void WidgetInventoryManager::on_pushButtonDetails_clicked(bool checked)
{
    SearchDetails=checked;
}

void WidgetInventoryManager::on_pushButtonCostPrice_clicked(bool checked)
{
    SearchCostPrice=checked;
}

void WidgetInventoryManager::on_pushButtonPrice_clicked(bool checked)
{
    SearchPrice=checked;
}

void WidgetInventoryManager::on_pushButtonAmount_clicked(bool checked)
{
    SearchAmount=checked;
}

void WidgetInventoryManager::on_pushButtonInventoryId_clicked(bool checked)
{
    SearchInventoryId=checked;
}


void WidgetInventoryManager::on_pushButtonCategory_clicked(bool checked)
{
    SearchCategory=checked;
}

void WidgetInventoryManager::InitLineEditInputMode()
{
    // 设置商品ID的正则表达式
    QRegExp rxId("[0-9]{1,10}"); // 1到10位数字
    QRegExpValidator *validatorId = new QRegExpValidator(rxId, this);
    ui->LineEditCommodityId->setValidator(validatorId);
    ui->lineEditInventoryId->setValidator(validatorId);
    // 设置商品名称的最大长度
    ui->LineEditCommodityName->setMaxLength(255); // 最大长度为255

    // 设置商品详情的最大长度
    ui->lineEditDetails->setMaxLength(35565); // 最大长度

    // 设置销售时间的格式
    ui->lineEditSellByTime->setInputMask("9999-99-99"); // YYYY-MM-DD

    // 设置价格和成本价的浮点数范围
    QDoubleValidator *validatorPrice = new QDoubleValidator(this);
    validatorPrice->setRange(0, 1e10, 2); // 价格范围
    ui->lineEditMinPrice->setValidator(validatorPrice);
    ui->lineEditMaxPrice->setValidator(validatorPrice);

    QDoubleValidator *validatorCostPrice = new QDoubleValidator(this);
    validatorCostPrice->setRange(0, 1e10, 2); // 成本价范围
    ui->lineEditMinCostPrice->setValidator(validatorCostPrice);
    ui->lineEditMaxCostPrice->setValidator(validatorCostPrice);

    // 设置数量的整数范围
    QIntValidator *validatorAmount = new QIntValidator(this);
    validatorAmount->setRange(0, 1e9); // 数量范围
    ui->lineEditMinAmount->setValidator(validatorAmount);
    ui->lineEditMaxAmount->setValidator(validatorAmount);
}

void WidgetInventoryManager::InitBoolSearchState()
{
    bool checked=false;
    SearchName=checked;
    SearchCommodityId=checked;
    SearchSellByTime=checked;
    SearchDetails=checked;
    SearchPrice=checked;
    SearchCostPrice=checked;
    SearchAmount=checked;
    SearchInventoryId=checked;
    SearchCategory=checked;
}

