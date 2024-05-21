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
            FlatButton->setOverlayStyle(Material::TintedOverlay);
        }
    }

    QList<QtMaterialFlatButton*> buttons = {ui->pushButtonFrontPage,ui->pushButtonBackPage,
                                             ui->pushButtonNextPage,ui->pushButtonPrevPage};

    for(auto i:buttons){
        i->setOverlayStyle(Material::TintedOverlay);
        i->setUseThemeColors(false);
        i->setBackgroundColor(QColor("#00bcd4"));
        i->setForegroundColor(QColor("#ffffff"));
        i->setOverlayColor(QColor("#00bcd4"));
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


QString WidgetOrderManager::fillSpace(const QString &str, int width) {
    int len = 0;
    for (const QChar &c : str) {
        if (c.unicode() >= 0x4E00 && c.unicode() <= 0x9FA5) { // 判断是否为汉字
            len += 2; // 汉字长度为2
        } else {
            len += 1; // 其他字符长度为1
        }
    }
    QString result = str;
    while (len < width) {
        result.append(' ');
        len += 1;
    }

    return result;
}
void WidgetOrderManager::on_pushButtonOutPutOrder_clicked()
{
    if(ui->tableViewOrder->currentIndex().row()==-1)
    {

        QMessageBox::warning(this,"导出失败","请选中订单后再导出!");
        return;
    }
    // 获取文件保存路径
    QString filePath = QFileDialog::getSaveFileName(this, tr("保存订单"),
                                                    tr("订单编号%1详情页.html")
                                                .arg(p_OrderTableService->getOTable()->getInveListOrder(ui->tableViewOrder->currentIndex()).getOrderId()),
                        tr("HTML Files (*.html)"));
    if (filePath.isEmpty()) {
        return;  // 用户取消操作
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, tr("警告"), tr("无法打开文件"));
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8"); // 设置文本流编码为UTF-8

    QVector<QVector<QVariant>> comlist = p_GoodsTableService->getGTable()->getGoodsList();

    // HTML开头
    out << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>" << tr("订单详情") << "</title>\n</head>\n<body>\n";
    out<<"<h1>"<<tr("%1").arg(PageConfig::getSupermarketName())<<"</h2>\n";
    out << "<h2>" << tr("订单详情") << "</h2>\n";
    out << "<table border=\"1\" cellspacing=\"0\" cellpadding=\"5\">\n";
    out << "<tr>\n"
        << "<th>" << tr("商品编号") << "</th>"
        << "<th>" << tr("商品名称") << "</th>"
        << "<th>" << tr("商品保质期") << "</th>"
        << "<th>" << tr("商品单价") << "</th>"
        << "<th>" << tr("商品数量") << "</th>"
        << "<th>" << tr("商品总价") << "</th>"
        << "</tr>\n";

    for (const auto& commodity : comlist) {
        out << "<tr>\n"
            << "<td>" << commodity[0].toString() << "</td>"
            << "<td>" << commodity[1].toString() << "</td>"
            << "<td>" << commodity[2].toString() << "</td>"
            << "<td>" << commodity[3].toString() << "</td>"
            << "<td>" << commodity[4].toString() << "</td>"
            << "<td>" << commodity[5].toString() << "</td>"
            << "</tr>\n";
    }

    out << "</table>\n";

    // 打印订单信息
    out << "<h3>" << tr("订单信息") << "</h3>\n";
    out << "<p>" << tr("<b>顾客姓名:   </b>") << ui->labelUserName->text() << "</p>\n"
        << "<p>" << tr("<b>顾客等级:   </b>") << ui->labelUserLevel->text() << "</p>\n"
        << "<p>" << tr("<b>手机号码:   </b>") << ui->labelPhoneNumber->text() << "</p>\n"
        << "<p>" << tr("<b>顾客积分:   </b>") << ui->labelUserPoint->text() << "</p>\n"
        << "<p>" << tr("<b>订单日期:   </b>") << ui->labelOrderDate->text() << "</p>\n"
        << "<p>" << tr("<b>商品件数:   </b>") << ui->labelItemCount->text() << "</p>\n"
        << "<p>" << tr("<b>应付:       </b>") << ui->labelTotalPrice->text() << "</p>\n"
        << "<p>" << tr("<b>实付:       </b>") << ui->labelPaidPrice->text()  << "</p>\n"
        << "<p>" << tr("<b>收银员姓名: </b>") << ui->labelCashierName->text() << "</p>\n"
        << "<p>" << tr("<b>订单状态:   </b>") << ui->labelOrderStage->text() << "</p>\n";

    // HTML结尾
    out << "</body>\n</html>\n";

    file.close();
}
