#include "widgetvipmanager.h"
#include "ui_widgetvipmanager.h"

WidgetVipManager::WidgetVipManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetVipManager)
{
    ui->setupUi(this);
}

WidgetVipManager::~WidgetVipManager()
{
    delete ui;
}
