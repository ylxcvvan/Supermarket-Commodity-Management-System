#include "mainwidget.h"
#include "ui_mainwidget.h"

#include<QDebug>
MainWidget::MainWidget(QWidget *parent,bool isadmin)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    ,pcashiwidget(new CashierWidget(this))
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(pcashiwidget); 

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_toolButtonMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

