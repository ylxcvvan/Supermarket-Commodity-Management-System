#include "widgetturnover.h"
#include "controller/database/sqlorder.h"
#include "ui_widgetturnover.h"

widgetturnover::widgetturnover(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::widgetturnover)
    ,p_OrderTableService(new OrderTableService)
{
    ui->setupUi(this);
    ui->tableViewOrder->setModel(p_OrderTableService->getOTable());
    //设置order表的样式
    ui->tableViewOrder->setCornerButtonEnabled(false);
    ui->tableViewOrder->setAlternatingRowColors(true);
    ui->tableViewOrder->setSelectionBehavior(QAbstractItemView::SelectRows);


    for (int i = 0; i < ui->tableViewOrder->horizontalHeader()->count(); ++i) {
        ui->tableViewOrder->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    if(ui->tableViewOrder->horizontalHeader()->count()>=1)
        ui->tableViewOrder->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    //设置单击表头排序
    ui->tableViewOrder->setSortingEnabled(true);
    connect(ui->tableViewOrder->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    loadModelOrder();
}

widgetturnover::~widgetturnover()
{
    delete ui;
    delete p_OrderTableService;
}

void widgetturnover::loadModelOrder()
{
    int index = ui->comboBoxRange->currentIndex();
    QDateTime begin;
    QDateTime end;
    QString format = "yyyy-MM-dd HH:mm:ss";
    QString be,en;
    if(index==0)
    {
        be = QString("%1-%2-%3 00:00:00").arg(year).arg(month, 2, 10, QChar('0')).arg(today, 2, 10, QChar('0'));
        en = QString("%1-%2-%3 23:59:59").arg(year).arg(month, 2, 10, QChar('0')).arg(today, 2, 10, QChar('0'));

    }
    else if(index==1)
    {
        be = QString("%1-%2-%3 00:00:00").arg(year).arg(month, 2, 10, QChar('0')).arg(today-dayofweek+1, 2, 10, QChar('0'));
        en = QString("%1-%2-%3 23:59:59").arg(year).arg(month, 2, 10, QChar('0')).arg(today, 2, 10, QChar('0'));
    }
    else if(index==2)
    {
        be = QString("%1-%2-%3 00:00:00").arg(year).arg(month, 2, 10, QChar('0')).arg(1,2,10,QChar('0'));
        en = QString("%1-%2-%3 23:59:59").arg(year).arg(month, 2, 10, QChar('0')).arg(daysinmonth,2,10,QChar('0'));
    }
    else if(index==3)
    {
        if(month < 7)
        {
            be = QString("%1-%2-%3 00:00:00").arg(year).arg(1,2,10,QChar('0')).arg(1,2,10,QChar('0'));
            en = QString("%1-%2-%3 23:59:59").arg(year).arg(6,2,10,QChar('0')).arg(30,2,10,QChar('0'));
        }
        else{
            be = QString("%1-%2-%3 00:00:00").arg(year).arg(7,2,10,QChar('0')).arg(1,2,10,QChar('0'));
            en = QString("%1-%2-%3 23:59:59").arg(year).arg(12,2,10,QChar('0')).arg(31,2,10,QChar('0'));
        }
    }
    else if(index==4)
    {
        be = QString("%1-%2-%3 00:00:00").arg(year).arg(1,2,10,QChar('0')).arg(1,2,10,QChar('0'));
        en = QString("%1-%2-%3 23:59:59").arg(year).arg(12,2,10,QChar('0')).arg(31,2,10,QChar('0'));
    }
    qDebug()<<be<<" "<<en;
    begin = QDateTime::fromString(be,format);
    end = QDateTime::fromString(en,format);
    qDebug()<<begin<<' '<<end;
    p_OrderTableService->setOList(SqlOrder::Query(-1,begin,end));
    qDebug()<<year<<" "<<month<<" "<<today<<" "<<dayofweek;
    gettotal_anmount();
    p_OrderTableService->getOTable()->setPageSize(PageConfig::getOrdTableMaxRow());
    on_spinBoxPageJump_valueChanged(1);
    ui->spinBoxPageJump->setValue(1);
    ui->spinBoxPageJump->setMaximum(p_OrderTableService->getOTable()->pageCount());
    ui->LabelTotalPages->setText(tr("%1").arg(p_OrderTableService->getOTable()->pageCount()));

}

void widgetturnover::gettotal_anmount()
{
    auto glist = p_OrderTableService->getOTable()->getOrderList();
    double total = 0.0;
    int amount = 0;
    for(auto i : glist){
        total += i.getTotalPrice();
        amount +=1;
    }
    ui->amount->setText(tr("%1").arg(amount));
    ui->total->setText(tr("%1").arg(total));
}

void widgetturnover::on_comboBoxRange_currentIndexChanged(int index)
{
    loadModelOrder();
    gettotal_anmount();
}

void widgetturnover::on_pushButtonFrontPage_clicked()
{

    p_OrderTableService->getOTable()->setCurrentPage(0);
    ui->spinBoxPageJump->setValue(1);
}


void widgetturnover::on_pushButtonPrevPage_clicked()
{

    int currentPage = p_OrderTableService->getOTable()->currentPageNumber();
    if (currentPage > 0) {
        p_OrderTableService->getOTable()->setCurrentPage(currentPage - 1);
        ui->spinBoxPageJump->setValue(currentPage);
    }
}


void widgetturnover::on_spinBoxPageJump_valueChanged(int arg1)
{

    p_OrderTableService->getOTable()->setCurrentPage(arg1- 1);
}


void widgetturnover::on_pushButtonNextPage_clicked()
{

    int currentPage = p_OrderTableService->getOTable()->currentPageNumber();
    if (currentPage < p_OrderTableService->getOTable()->pageCount() - 1) {
        p_OrderTableService->getOTable()->setCurrentPage(currentPage + 1);
        ui->spinBoxPageJump->setValue(currentPage + 2);
    }
}


void widgetturnover::on_pushButtonBackPage_clicked()
{

    int lastPage = p_OrderTableService->getOTable()->pageCount() - 1;
    p_OrderTableService->getOTable()->setCurrentPage(lastPage);
    ui->spinBoxPageJump->setValue(lastPage + 1);
}

