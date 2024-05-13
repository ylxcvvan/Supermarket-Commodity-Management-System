#include "widgetordermanager.h"
#include "ui_widgetordermanager.h"

WidgetOrderManager::WidgetOrderManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetOrderManager)
{
    ui->setupUi(this);
}

WidgetOrderManager::~WidgetOrderManager()
{
    delete ui;
}
