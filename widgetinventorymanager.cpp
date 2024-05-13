#include "widgetinventorymanager.h"
#include "ui_widgetinventorymanager.h"

WidgetInventoryManager::WidgetInventoryManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetInventoryManager)
{
    ui->setupUi(this);
}

WidgetInventoryManager::~WidgetInventoryManager()
{
    delete ui;
}
