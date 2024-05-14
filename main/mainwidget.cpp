#include "mainwidget.h"
#include "ui_mainwidget.h"
#include"mysqloperate.h"
#include<QDebug>
MainWidget::MainWidget(QWidget *parent,bool isadmin)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    ,p_pagemain(new PageMain(this))
    ,p_pageconfig(new PageConfig(this))
    ,p_pagehelp(new PageHelp(this))
{
    ui->setupUi(this);
    //设定是否是管理员
    isAdmin=isadmin;
    MySql::getInstance().getdb();
    //添加page页到stackedWidget中
    ui->stackedWidget->addWidget(p_pagemain);
    ui->stackedWidget->addWidget(p_pageconfig);
    ui->stackedWidget->addWidget(p_pagehelp);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_toolButtonMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




void MainWidget::on_toolButtontConfig_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWidget::on_toolButtonHelp_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

