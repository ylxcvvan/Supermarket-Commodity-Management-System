#include "widgetinventorymanager.h"
#include "ui_widgetinventorymanager.h"
#include<QMessageBox>
#include<qdebug.h>
WidgetInventoryManager::WidgetInventoryManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetInventoryManager)
    ,p_InventoryTableService(new InventoryTableService)
    ,p_ComItemTableService(new ComItemTableService)
{
    ui->setupUi(this);

    //设置表样式
    ui->tableView->setCornerButtonEnabled(false);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置可以编辑
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //设置“商品类别”下拉框
    for(auto &s:p_InventoryTableService->getComboBoxDelegate()->getComBoBoxCategory())
    {
        ui->comboBoxCategory->addItem(s);
    }


    //设置单击表头排序
    ui->tableView->setSortingEnabled(true);
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    //设置商品类型的comboBox
    ui->tableView->setItemDelegateForColumn(3,p_InventoryTableService->getComboBoxDelegate());

    //设置当前表模型
    ui->tableView->setModel(p_InventoryTableService->getITable());
    ui->tableView_2->setModel(p_ComItemTableService-)
    ui->dateEdit->setDate(QDate::currentDate().addDays(PageConfig::getAddDays()));
    ui->WidgetPutIn->hide();

    InitBoolSearchState();
    InitLineEditInputMode();
    PushButtonInit();
}
WidgetInventoryManager::~WidgetInventoryManager()
{
    delete p_InventoryTableService;
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
    QDate sellbytime=SearchSellByTime?ui->dateEdit->date():QDate();

    double minprice=SearchPrice?ui->lineEditMinPrice->value():-1;
    double maxprice=SearchPrice?ui->lineEditMaxPrice->value():1e10;

    double mincostprice=SearchCostPrice?ui->lineEditMinCostPrice->value():-1;
    double maxcostprice=SearchCostPrice?ui->lineEditMaxCostPrice->value():1e10;

    double minamount=SearchAmount?ui->lineEditMinAmount->value():-1;
    double maxamount=SearchAmount?ui->lineEditMaxAmount->value():1e10;


    p_InventoryTableService->setIList(SqlInventory::Query(id,cid,cname,category,details,sellbytime
                                                                ,minprice,maxprice,mincostprice,maxcostprice
                                                                ,minamount,maxamount));

    //设置当前模型_OLD版本是这样更新的，新版本不需要，注释掉了
    // ui->tableView->setModel(p_InventoryTableService->getITable());
    ui->tableView->update();
    for (int i = 0; i < ui->tableView->horizontalHeader()->count(); ++i) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    // 设置商品描述的表头为自适应内容长度，确保内容完全展现
    if(ui->tableView->horizontalHeader()->count()>=4)
        ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    //更改页数与最大数量
    p_InventoryTableService->getITable()->setPageSize(PageConfig::getInveTableMaxRow());
    on_spinBoxPageJump_valueChanged(1);
    ui->spinBoxPageJump->setValue(1);
    ui->spinBoxPageJump->setMaximum(p_InventoryTableService->getITable()->pageCount());
    ui->LabelTotalPages->setText(tr("%1").arg(p_InventoryTableService->getITable()->pageCount()));

}


void WidgetInventoryManager::sortByColumn(int column)
{
    Qt::SortOrder order = ui->tableView->horizontalHeader()->sortIndicatorOrder();
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

void WidgetInventoryManager::PushButtonInit()
{
    const QList<QWidget *> children = this->findChildren<QWidget *>();

    for(QWidget *child : children){
         QtMaterialFlatButton *FlatButton = qobject_cast<QtMaterialFlatButton *>(child);

        if(FlatButton){
             FlatButton->setHaloVisible(false);
             FlatButton->setTextAlignment(Qt::AlignCenter);

             FlatButton->setBackgroundColor(QColor("#feffef"));
             FlatButton->setForegroundColor(QColor("#fd8f01"));
             FlatButton->setOverlayColor(QColor("#ffffff"));
         }
    }

    QList<QtMaterialFlatButton*> buttons = {ui->pushButtonFrontPage,ui->pushButtonBackPage,
                                             ui->pushButtonNextPage,ui->pushButtonPrevPage};

    for(auto i:buttons){
        i->setOverlayStyle(Material::TintedOverlay);
        i->setUseThemeColors(false);
        i->setBackgroundColor(QColor("#00bcd4"));
        i->setForegroundColor(QColor("ffffff"));
        i->setOverlayColor(QColor("00bcd4"));
        i->setRole(Material::Primary);
        i->setTextAlignment(Qt::AlignCenter);
    }
}

void WidgetInventoryManager::on_pushButtonFrontPage_clicked()
{
    p_InventoryTableService->getITable()->setCurrentPage(0);
    ui->spinBoxPageJump->setValue(1);
}


void WidgetInventoryManager::on_pushButtonPrevPage_clicked()
{
    int currentPage = p_InventoryTableService->getITable()->currentPageNumber();
    if (currentPage > 0) {
        p_InventoryTableService->getITable()->setCurrentPage(currentPage - 1);
        ui->spinBoxPageJump->setValue(currentPage);
    }
}


void WidgetInventoryManager::on_spinBoxPageJump_valueChanged(int arg1)
{
    p_InventoryTableService->getITable()->setCurrentPage(arg1- 1);
}


void WidgetInventoryManager::on_pushButtonNextPage_clicked()
{
    int currentPage = p_InventoryTableService->getITable()->currentPageNumber();
    if (currentPage < p_InventoryTableService->getITable()->pageCount() - 1) {
        p_InventoryTableService->getITable()->setCurrentPage(currentPage + 1);
         ui->spinBoxPageJump->setValue(currentPage + 2);
    }
}


void WidgetInventoryManager::on_pushButtonBackPage_clicked()
{
    int lastPage = p_InventoryTableService->getITable()->pageCount() - 1;
    p_InventoryTableService->getITable()->setCurrentPage(lastPage);
     ui->spinBoxPageJump->setValue(lastPage + 1);
}

void WidgetInventoryManager::on_pushButtonInPutExcel_clicked(bool checked)
{
    if(!checked)
    {
        ui->WidgetPutIn->hide();
    }
    else
        ui->WidgetPutIn->show();
}

