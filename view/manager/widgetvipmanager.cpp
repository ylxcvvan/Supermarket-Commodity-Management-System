#include "widgetvipmanager.h"
#include "ui_widgetvipmanager.h"
#include "view/page/pageconfig.h"

WidgetVipManager::WidgetVipManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetVipManager)
    , p_viptableservice(new VipTableService())
{
    ui->setupUi(this);

    ui->tableview->setModel(p_viptableservice->getTable());
    //设置order表的样式
    ui->tableview->setCornerButtonEnabled(false);
    ui->tableview->setAlternatingRowColors(true);
    ui->tableview->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->dateTimeEditBegin->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime());
    //设置单击表头排序
    ui->tableview->setSortingEnabled(true);
    connect(ui->tableview->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    ui->widgetAddVip->hide();

    loadModelVip();
    pushButtonInit();
}

WidgetVipManager::~WidgetVipManager()
{
    delete p_viptableservice;
    delete ui;
}

void WidgetVipManager::loadModelVip()
{
    QString name = SearchName? ui->lineEditName->text():"";
    QString phonum = SearchPhoNum? ui->lineEditPhoneNum->text():"";
    double minpoint = SearchPoint? ui->doubleSpinBoxMinP->value():-1;
    double maxpoint = SearchPoint? ui->doubleSpinBoxMaxp->value():1e10;
    int minl = SearchLev? ui->spinBoxMinL->value():-1;
    int maxl = SearchLev? ui->spinBoxMaxL->value():1e9;
    QDate minD = SearchDate? ui->dateTimeEditBegin->date():QDate();
    QDate maxD = SearchDate? ui->dateTimeEditEnd->date():QDate();


    p_viptableservice->setTable(SqlVip::Query(-1,name,phonum,minpoint,maxpoint,minl,maxl,minD,maxD));

    for (int i = 0; i < ui->tableview->horizontalHeader()->count(); ++i) {
        ui->tableview->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    if(ui->tableview->horizontalHeader()->count()>=1)
        ui->tableview->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    //更改页数与最大数量
    p_viptableservice->getTable()->setPageSize(PageConfig::getVipTableMaxRow());
    on_currentPage_valueChanged(1);
    ui->currentPage->setValue(1);
    ui->currentPage->setMaximum(p_viptableservice->getTable()->pageCount());
    ui->totalpages->setText(tr("%1").arg(p_viptableservice->getTable()->pageCount()));

}

void WidgetVipManager::pushButtonInit()
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
    QList<QtMaterialFlatButton*> buttons = {ui->fontpage,ui->nextpage,
                                             ui->prepage,ui->tailpage};

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

void WidgetVipManager::sortByColumn(int column)
{
    Qt::SortOrder order = ui->tableview->horizontalHeader()->sortIndicatorOrder();
    p_viptableservice->sortByColumn(column,order);
}

void WidgetVipManager::on_pushButtonName_clicked(bool checked)
{
    SearchName = checked;
}

void WidgetVipManager::on_pushButtonSearch_clicked()
{
    loadModelVip();
}

void WidgetVipManager::on_pushButtonRegTime_clicked(bool checked)
{
    SearchDate = checked;
}


void WidgetVipManager::on_pushButtonPhoneNum_clicked(bool checked)
{
    SearchPhoNum = checked;
}


void WidgetVipManager::on_pushButtonPoint_clicked(bool checked)
{
    SearchPoint = checked;
}


void WidgetVipManager::on_pushButtonLevel_clicked(bool checked)
{
    SearchLev = checked;
}

void WidgetVipManager::on_fontpage_clicked()
{
    p_viptableservice->getTable()->setCurrentPage(0);
    ui->currentPage->setValue(1);
}


void WidgetVipManager::on_prepage_clicked()
{
    int currentPage = p_viptableservice->getTable()->currentPageNumber();
    if (currentPage > 0) {
        p_viptableservice->getTable()->setCurrentPage(currentPage - 1);
        ui->currentPage->setValue(currentPage);
    }
}

void WidgetVipManager::on_currentPage_valueChanged(int arg1)
{
    p_viptableservice->getTable()->setCurrentPage(arg1-1);
}

void WidgetVipManager::on_nextpage_clicked()
{
    int currentPage = p_viptableservice->getTable()->currentPageNumber();
    if (currentPage <p_viptableservice->getTable()->pageCount() - 1) {
       p_viptableservice->getTable()->setCurrentPage(currentPage + 1);
        ui->currentPage->setValue(currentPage + 2);
    }
}

void WidgetVipManager::on_tailpage_clicked()
{

    int lastPage = p_viptableservice->getTable()->pageCount() - 1;
    p_viptableservice->getTable()->setCurrentPage(lastPage);
    ui->currentPage->setValue(lastPage + 1);
}



void WidgetVipManager::on_pushButtonAdd_clicked(bool checked)
{
    if(checked)
    {
        ui->WidgetLevel_Point->hide();
        ui->WidgetVipDetails->hide();
        ui->widgetAddVip->show();

    }
    else
    {
        ui->widgetAddVip->hide();
        ui->WidgetLevel_Point->show();
        ui->WidgetVipDetails->show();
    }
}

