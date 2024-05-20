#include "widgetordermanager.h"
#include "controller/database/sqlcashier.h"
#include "controller/database/sqlcommondity.h"
#include "ui_widgetordermanager.h"


WidgetOrderManager::WidgetOrderManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetOrderManager)
    ,p_OrderTableService(new OrderTableService)
    ,p_GoodsTableService(new GoodsTableService)
{
    ui->setupUi(this);

    loadModelOrder();
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
    ui->tableViewOrderItem->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewOrderItem->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置单击表头排序
    ui->tableViewOrder->setSortingEnabled(true);
    connect(ui->tableViewOrder->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    ui->dateTimeEditBegin->setDateTime(QDateTime::currentDateTime().addDays(-1));
    ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime());
    InitLineEditInputMode();
    PushButtonInit();
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


    //更改页数与最大数量
     p_OrderTableService->getOTable()->setPageSize(PageConfig::getOrdTableMaxRow());
     on_spinBoxPageJump_valueChanged(1);
     ui->spinBoxPageJump->setValue(1);
     ui->spinBoxPageJump->setMaximum(p_OrderTableService->getOTable()->pageCount());
     ui->LabelTotalPages->setText(tr("%1").arg(p_OrderTableService->getOTable()->pageCount()));



}

void WidgetOrderManager::PushButtonInit()
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

void WidgetOrderManager::InitLineEditInputMode()
{
    // 设置商品ID的正则表达式
    QRegExp rxId("[0-9]{1,10}"); // 1到10位数字
    QRegExpValidator *validatorId = new QRegExpValidator(rxId, this);
    ui->lineEditOrderId->setValidator(validatorId);
    ui->lineEditCashierId->setValidator(validatorId);
    ui->lineEditUserId->setValidator(validatorId);
}

void WidgetOrderManager::sortByColumn(int column)
{
    Qt::SortOrder order = ui->tableViewOrder->horizontalHeader()->sortIndicatorOrder();
    p_OrderTableService->sortByColumn(column,order);
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

    auto viplist=SqlVip::Query(order.getUserId());

    if(!viplist.isEmpty())
    {
        Vip vip=viplist.front();
        ui->labelUserName->setText(vip.getName());
        ui->labelUserLevel->setText(tr("等级 %1").arg(vip.getLevel()));
        ui->labelPhoneNumber->setText(vip.getPhoneNumber());
        ui->labelUserPoint->setText(tr("%1 分").arg(vip.getPoint()));
    }
    //设置右下角的属性
    else
    {
        ui->labelUserName->setText("无");
        ui->labelUserLevel->setText(tr("%1").arg("无"));
        ui->labelPhoneNumber->setText("无");
        ui->labelUserPoint->setText(tr("%1").arg("无"));
    }

    ui->labelOrderDate->setText(order.getOrderTime().toString("yyyy-MM-dd"));
    ui->labelItemCount->setText(tr("%1 件").arg(newmodel.size()));
    ui->labelTotalPrice->setText(tr("%1 元").arg(order.getTotalPrice()));
    ui->labelPaidPrice->setText(tr("%1 元").arg(order.getPaidPrice()));
    //收银员姓名TODO
    ui->labelCashierName->setText(SqlCashier::query(order.getCashierId()).getName());
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
    p_OrderTableService->getOTable()->setCurrentPage(0);
    ui->spinBoxPageJump->setValue(1);
}


void WidgetOrderManager::on_pushButtonPrevPage_clicked()
{
    int currentPage = p_OrderTableService->getOTable()->currentPageNumber();
    if (currentPage > 0) {
        p_OrderTableService->getOTable()->setCurrentPage(currentPage - 1);
        ui->spinBoxPageJump->setValue(currentPage);
    }
}


void WidgetOrderManager::on_spinBoxPageJump_valueChanged(int arg1)
{
     p_OrderTableService->getOTable()->setCurrentPage(arg1- 1);
}


void WidgetOrderManager::on_pushButtonNextPage_clicked()
{
    int currentPage = p_OrderTableService->getOTable()->currentPageNumber();
    if (currentPage <p_OrderTableService->getOTable()->pageCount() - 1) {
        p_OrderTableService->getOTable()->setCurrentPage(currentPage + 1);
        ui->spinBoxPageJump->setValue(currentPage + 2);
    }
}


void WidgetOrderManager::on_pushButtonBackPage_clicked()
{
    int lastPage = p_OrderTableService->getOTable()->pageCount() - 1;
    p_OrderTableService->getOTable()->setCurrentPage(lastPage);
    ui->spinBoxPageJump->setValue(lastPage + 1);
}


#include <QFileDialog>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVariant>

void WidgetOrderManager::on_pushButtonOutPutOrder_clicked()
{
    // 获取文件保存路径
    QString filePath = QFileDialog::getSaveFileName(this, "保存订单", QCoreApplication::applicationDirPath(), "Text Files (*.txt)");
    if (filePath.isEmpty()) {
        return;  // 用户取消操作
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Warning", "Failed to open file");
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8"); // 设置文本流编码为UTF-8

    QVector<QVector<QVariant>> comlist = p_GoodsTableService->getGTable()->getGoodsList();
    // 写入商品信息
    out << "| " << qSetFieldWidth(10) << tr("商品编号") << qSetFieldWidth(0)
        << "| " << qSetFieldWidth(10) << tr("商品名称") << qSetFieldWidth(0)
        << "| " << qSetFieldWidth(20) << tr("商品保质期") << qSetFieldWidth(0)
        << "| " << qSetFieldWidth(10) << tr("商品单价") << qSetFieldWidth(0)
        << "| " << qSetFieldWidth(10) << tr("商品数量") << qSetFieldWidth(0)
        << "| " << qSetFieldWidth(10) << tr("商品总价") << qSetFieldWidth(0) << "|\n";

    for (const auto& commodity : comlist) {
        out << "| " << qSetFieldWidth(10) << commodity[0].toString() << qSetFieldWidth(0)
            << "| " << qSetFieldWidth(10) << commodity[1].toString() << qSetFieldWidth(0)
            << "| " << qSetFieldWidth(20) << commodity[2].toString() << qSetFieldWidth(0)
            << "| " << qSetFieldWidth(10) << commodity[3].toString() << qSetFieldWidth(0)
            << "| " << qSetFieldWidth(10) << commodity[4].toString() << qSetFieldWidth(0)
            << "| " << qSetFieldWidth(10) << commodity[5].toString() << qSetFieldWidth(0) << "|\n";
    }

    // 假设你有一个 Order 对象 order，包含订单的详细信息
    out << "| " << qSetFieldWidth(0) << tr("顾客姓名:") << qSetFieldWidth(0) << " " << ui->labelUserName->text()
        << " | " << qSetFieldWidth(0) << tr("顾客等级:") << qSetFieldWidth(0) << " " << ui->labelUserLevel->text() << " |\n"
        << "| " << qSetFieldWidth(0) << tr("手机号码:") << qSetFieldWidth(0) << " " << ui->labelPhoneNumber->text()
        << " | " << qSetFieldWidth(0) << tr("顾客积分:") << qSetFieldWidth(0) << " " << ui->labelUserPoint->text() << " " << tr("分") << " |\n"
        << "| " << qSetFieldWidth(0) << tr("订单日期:") << qSetFieldWidth(0) << " " << ui->labelOrderDate->text()
        << " | " << qSetFieldWidth(0) << tr("商品件数:") << qSetFieldWidth(0) << " " << ui->labelItemCount->text() << " " << tr("件") << " |\n"
        << "| " << qSetFieldWidth(0) << tr("应付:") << qSetFieldWidth(0) << " " << ui->labelTotalPrice->text()
        << " | " << qSetFieldWidth(0) << tr("实付:") << qSetFieldWidth(0) << " " << ui->labelPaidPrice->text() << " |\n"
        << "| " << qSetFieldWidth(0) << tr("收银员姓名:") << qSetFieldWidth(0) << " " << ui->labelCashierName->text()
        << " | " << qSetFieldWidth(0) << tr("订单状态:") << qSetFieldWidth(0) << " " << ui->labelOrderStage->text() << " |\n";





    file.close();
}
