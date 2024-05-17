#include "pagemain.h"
#include "ui_pagemain.h"
#include "controller/database/sqlcommondityitem.h"
#include "controller/database/sqlorder.h"
PageMain::PageMain(QWidget *parent,bool isAdmin)//店员和管理员未区分TODO
    : QWidget(parent)
    , ui(new Ui::PageMain)
    ,p_widgetCashier(new WidgetCashierManager(this))
    ,p_widgetInventory(new WidgetInventoryManager(this))
    ,p_widgetOrder(new WidgetOrderManager(this))
    ,p_widgetVip(new WidgetVipManager(this))
{
    ui->setupUi(this);


    widgetVec.push_back(p_widgetCashier);
    widgetVec.push_back(p_widgetInventory);
    widgetVec.push_back(p_widgetOrder);
    widgetVec.push_back(p_widgetVip);

    toolbtnVec.push_back(ui->toolButtonCashier);
    toolbtnVec.push_back(ui->toolButtonInventory);
    toolbtnVec.push_back(ui->toolButtonOrder);
    toolbtnVec.push_back(ui->toolButtonVip);

    for(auto &widget:widgetVec)
    {
        ui->stackedWidget->addWidget(widget);
    }

}

PageMain::~PageMain()
{
    delete ui;
}

void PageMain::setOtherWidgetUnchecked(int index)
{
    for(auto &btn:toolbtnVec)
    {
        btn->setChecked(false);
    }
    toolbtnVec[index]->setChecked(true);
}

void PageMain::on_toolButtonCashier_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setOtherWidgetUnchecked(0);
}

void PageMain::on_toolButtonInventory_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    p_widgetInventory->loadModel();
    setOtherWidgetUnchecked(1);
}


void PageMain::on_toolButtonOrder_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    setOtherWidgetUnchecked(2);

    SqlOrder::Query();
}


void PageMain::on_toolButtonVip_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    setOtherWidgetUnchecked(3);
}

