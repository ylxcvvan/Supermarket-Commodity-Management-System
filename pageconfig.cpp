#include "pageconfig.h"
#include "ui_pageconfig.h"

PageConfig::PageConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageConfig)
{
    ui->setupUi(this);
}

PageConfig::~PageConfig()
{
    delete ui;
}
