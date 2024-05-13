#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "cashierwidget.h"
#include<QDebug>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    CashierWidget *pcashiwidget=new CashierWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(pcashiwidget);
    ui->stackedWidget->setCurrentWidget(pcashiwidget);
    ui->stackedWidget->show();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_toolButtonMain_clicked()
{

}

