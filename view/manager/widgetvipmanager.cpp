#include "widgetvipmanager.h"
#include "ui_widgetvipmanager.h"
#include "view/page/pageconfig.h"

WidgetVipManager::WidgetVipManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetVipManager)
    , viptableservice(new VipTableService())
{
    ui->setupUi(this);

    ui->tableview->setModel(viptableservice->getTable());
    //设置order表的样式
    ui->tableview->setCornerButtonEnabled(false);
    ui->tableview->setAlternatingRowColors(true);
    ui->tableview->setSelectionBehavior(QAbstractItemView::SelectRows);


    //设置单击表头排序
    ui->tableview->setSortingEnabled(true);
    connect(ui->tableview->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));


    for (int i = 0; i < ui->tableview->horizontalHeader()->count(); ++i) {
        ui->tableview->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    if(ui->tableview->horizontalHeader()->count()>=1)
        ui->tableview->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    //更改页数与最大数量
    viptableservice->getTable()->setPageSize(PageConfig::getOrdTableMaxRow());
    on_currentPage_valueChanged(1);
    ui->currentPage->setValue(1);
    ui->totalpages->setText(tr("%1").arg(viptableservice->getTable()->pageCount()));


    loadModelVip();
    pushButtonInit();
}

WidgetVipManager::~WidgetVipManager()
{
    delete viptableservice;
    delete ui;
}

void WidgetVipManager::loadModelVip()
{
    QString name = SearchName? ui->lineEditName->text():"";
    QString phonum = SearchPhoNum? ui->lineEditPhoneNum->text():"";
    double minpoint = SearchPoint? ui->doubleSpinBoxMinP->value():-1;
    double maxpoint = SearchPoint? ui->doubleSpinBoxMaxp->value():-1;
    int minl = SearchLev? ui->spinBoxMinL->value():-1;
    int maxl = SearchLev? ui->spinBoxMaxL->value():-1;
    QDate minD = SearchDate? ui->dateTimeEditBegin->date():QDate();
    QDate maxD = SearchDate? ui->dateTimeEditEnd->date():QDate();


    viptableservice->setTable(SqlVip::Query(-1,name,phonum,minpoint,maxpoint,minl,maxl,minD,maxD));
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


void WidgetVipManager::on_currentPage_valueChanged(int arg1)
{
    viptableservice->getTable()->setCurrentPage(arg1-1);
}

