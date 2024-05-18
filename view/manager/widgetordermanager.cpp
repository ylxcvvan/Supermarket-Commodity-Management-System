#include "widgetordermanager.h"
#include "ui_widgetordermanager.h"

WidgetOrderManager::WidgetOrderManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetOrderManager)
    ,p_OrderTableService(new OrderTableService)
{
    ui->setupUi(this);

    //设置表的样式
    ui->tableViewOrder->setCornerButtonEnabled(false);
    ui->tableViewOrder->setAlternatingRowColors(true);
    ui->tableViewOrder->setSelectionBehavior(QAbstractItemView::SelectRows);

    InitLineEditInputMode();
}

WidgetOrderManager::~WidgetOrderManager()
{
    delete p_OrderTableService;
    delete ui;
}

void WidgetOrderManager::loadModelOrder()
{
    int OrderId=searchOrderId?ui->lineEditOrderId->text().toInt():-1;
    int CashierId=searchCashierId?ui->lineEditCashierId->text().toInt():-1;
    int consumerid=searchUserId?ui->lineEditUserId->text().toInt():-1;
    QDateTime begindt=searchOrderTime?ui->dateTimeEditBegin->dateTime():QDateTime();
    QDateTime enddt=searchOrderTime?ui->dateTimeEditEnd->dateTime():QDateTime();
    double minTotalPrice=searchTotalPrice?ui->doubleSpinBoxMinTotalPrice->value():-1;
    double maxTotalPrice=searchTotalPrice?ui->doubleSpinBoxMaxTotalPrice->value():1e10;
    int orderstage=searchOrderStage?ui->comboBoxOrderStage->currentIndex():-1;
    p_OrderTableService->setOList(SqlOrder::Query(OrderId,begindt,enddt,orderstage,
                                                  minTotalPrice,maxTotalPrice,-1,1e10,consumerid,CashierId));
    ui->tableViewOrder->setModel(p_OrderTableService->getOTable());

    for (int i = 0; i < ui->tableViewOrder->horizontalHeader()->count(); ++i) {
        ui->tableViewOrder->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    // 设置商品描述的表头为自适应内容长度，确保内容完全展现
    ui->tableViewOrder->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void WidgetOrderManager::InitLineEditInputMode()
{
    // 设置商品ID的正则表达式
    QRegExp rxId("[0-9]{1,10}"); // 1到10位数字
    QRegExpValidator *validatorId = new QRegExpValidator(rxId, this);
    ui->lineEditOrderId->setValidator(validatorId);
    ui->lineEditCashierId->setValidator(validatorId);
    ui->lineEditUserId->setValidator(validatorId);
}

void WidgetOrderManager::on_pushButtonOrderId_clicked(bool checked)
{
    searchOrderId=checked;
}

void WidgetOrderManager::on_pushButtonOrderStage_clicked(bool checked)
{
    searchOrderStage=checked;
}

void WidgetOrderManager::on_pushButtonCashierId_clicked(bool checked)
{
    searchCashierId=checked;
}

void WidgetOrderManager::on_pushButtonUserId_clicked(bool checked)
{
    searchUserId=checked;
}


void WidgetOrderManager::on_pushButtonOrderTime_clicked(bool checked)
{
    searchOrderTime=checked;
}


void WidgetOrderManager::on_pushButtonTotalPrice_clicked(bool checked)
{
    searchTotalPrice=checked;
}


void WidgetOrderManager::on_pushButtonSelect_clicked()
{
    loadModelOrder();
}

