#include "pagemain.h"
#include "ui_pagemain.h"

PageMain::PageMain(QWidget *parent,bool isAdmin)//店员和管理员未区分TODO
    : QWidget(parent)
    , ui(new Ui::PageMain)
    ,p_widgetCashier(new WidgetCashierManager(this))
    ,p_widgetInventory(new WidgetInventoryManager(this))
    ,p_widgetOrder(new WidgetOrderManager(this))
    ,p_widgetVip(new WidgetVipManager(this))
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(p_widgetCashier);
    ui->stackedWidget->addWidget(p_widgetInventory);
    ui->stackedWidget->addWidget(p_widgetOrder);
    ui->stackedWidget->addWidget(p_widgetVip);

}

PageMain::~PageMain()
{
    delete ui;
}


void PageMain::on_toolButtonCashier_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void PageMain::on_toolButtonInventory_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void PageMain::on_toolButtonOrder_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void PageMain::on_toolButtonVip_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

