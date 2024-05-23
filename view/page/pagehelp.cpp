#include "pagehelp.h"
#include "ui_pagehelp.h"
#include"main/mainwidget.h"
PageHelp::PageHelp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageHelp)
{
    ui->setupUi(this);



    ui->label_4->setOpenExternalLinks(true);
}

PageHelp::~PageHelp()
{
    delete ui;
}

void PageHelp::on_pushButton_clicked()
{
    QMessageBox::aboutQt(this, tr("关于 Qt"));
}

