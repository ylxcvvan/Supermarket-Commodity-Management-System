#include "widgetordermanager.h"
#include "controller/database/sqlcommondity.h"
#include "ui_widgetordermanager.h"

WidgetOrderManager::WidgetOrderManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetOrderManager)
    ,p_OrderTableService(new OrderTableService)
    ,p_GoodsTableService(new GoodsTableService)
{
    ui->setupUi(this);

    //装载order表
    ui->tableViewOrder->setModel(p_OrderTableService->getOTable());
    //设置order表的样式
    ui->tableViewOrder->setCornerButtonEnabled(false);
    ui->tableViewOrder->setAlternatingRowColors(true);
    ui->tableViewOrder->setSelectionBehavior(QAbstractItemView::SelectRows);

    //装载orderitem表
    ui->tableViewOrderItem->setModel(p_GoodsTableService->getGTable());
    //设置orderitem表样式
    ui->tableViewOrderItem->setCornerButtonEnabled(false);
    ui->tableViewOrderItem->setAlternatingRowColors(true);
     ui->tableViewOrderItem->setSelectionBehavior(QAbstractItemView::SelectRows);

    InitLineEditInputMode();
}

WidgetOrderManager::~WidgetOrderManager()
{
    delete p_GoodsTableService;
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
    // 设置商品描述的表头为自适应内容长度，确保内容完全展现
    for (int i = 0; i < ui->tableViewOrder->horizontalHeader()->count(); ++i) {
        ui->tableViewOrder->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    if(ui->tableViewOrder->horizontalHeader()->count()>=1)
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


void WidgetOrderManager::on_tableViewOrder_doubleClicked(const QModelIndex &index)
{
    Order order=p_OrderTableService->getOTable()->getInveListOrder(index);

    QVector<OrderItem> OrderitemList=SqlOrderItem::Query(order.getOrderId());
    QVector<QVector<QVariant>>newmodel;
    for(const OrderItem& oitem:OrderitemList)
    {
        auto commodityitem=SqlCommondity::Query(oitem.getCommodityId()).front();
        QVector<QVariant>res{oitem.getCommodityId(),commodityitem.getName(),commodityitem.getSellByTime()
                              ,commodityitem.getPrice(),oitem.getCommodityAmount(),oitem.getTotalPrice()};
        newmodel.push_back(res);
    }

    Vip vip=SqlVip::Query(order.getUserId());

    //设置右下角的属性
    ui->labelUserName->setText(vip.getName());
    ui->labelUserLevel->setText(tr("等级 %1").arg(vip.getLevel()));
    ui->labelPhoneNumber->setText(vip.getPhoneNumber());
    ui->labelUserPoint->setText(tr("%1 分").arg(vip.getPoint()));
    ui->labelOrderDate->setText(order.getOrderTime().toString("yyyy-MM-dd"));
    ui->labelItemCount->setText(tr("%1 件").arg(newmodel.size()));
    ui->labelTotalPrice->setText(tr("%1 元").arg(order.getTotalPrice()));
    ui->labelPaidPrice->setText(tr("%1 元").arg(order.getPaidPrice()));
    //收银员姓名TODO
    //ui->labelCashierName->setText();
    ui->labelOrderStage->setText(ui->comboBoxOrderStage->itemText(static_cast<int>(order.getOrderStage())));

    //装载底层数据，更新表样式
    p_GoodsTableService->setGList(std::move(newmodel));
    for (int i = 0; i < ui->tableViewOrderItem->horizontalHeader()->count(); ++i) {
        ui->tableViewOrderItem->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    if(ui->tableViewOrderItem->horizontalHeader()->count()>=2)
        ui->tableViewOrderItem->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);


}


void WidgetOrderManager::on_pushButtonFrontPage_clicked()
{

}


void WidgetOrderManager::on_pushButtonPrevPage_clicked()
{

}


void WidgetOrderManager::on_spinBoxPageJump_valueChanged(int arg1)
{

}


void WidgetOrderManager::on_pushButtonNextPage_clicked()
{

}


void WidgetOrderManager::on_pushButtonBackPage_clicked()
{

}

