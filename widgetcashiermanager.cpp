#include "widgetcashiermanager.h"
#include "ui_widgetcashiermanager.h"

WidgetCashierManager::WidgetCashierManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetCashierManager)
{
    ui->setupUi(this);
}

WidgetCashierManager::~WidgetCashierManager()
{
    delete ui;
}
