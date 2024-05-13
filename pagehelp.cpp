#include "pagehelp.h"
#include "ui_pagehelp.h"

PageHelp::PageHelp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageHelp)
{
    ui->setupUi(this);
}

PageHelp::~PageHelp()
{
    delete ui;
}
