#include "mainwidget.h"
#include "ui_mainwidget.h"
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

    //连接数据库
    auto db =MySql::getInstance().getDatabase();

    //添加page页到stackedWidget中
    ui->stackedWidget->addWidget(p_pagemain);
    ui->stackedWidget->addWidget(p_pageconfig);
    ui->stackedWidget->addWidget(p_pagehelp);

    FrameLessInit();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::FrameLessInit()
{
    setWindowFlags(Qt::FramelessWindowHint);
    isMoveAllowed=false;
    isFullSceen=false;
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


void MainWidget::on_pushButtonMinmize_clicked()
{
    this->showMinimized();
}


void MainWidget::on_pushButtonMaxmize_clicked(bool checked)
{
        if(checked){
        this->showMaximized();
        //最大化以后给最大化按钮换个图标

    } //窗口不是最大化时，最大化窗口
    else{
        this->showNormal();
    }
}


void MainWidget::on_pushButtonExit_clicked()
{
    QApplication::quit();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->y() <= ui->widgetTitle->height()+ui->verticalLayout->margin()*1.5){
        isMoveAllowed = true;
        originalPos = e->pos();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(isMoveAllowed == true){
        if(ui->pushButtonMaxmize->isChecked()){
            on_pushButtonMaxmize_clicked(false);
            ui->pushButtonMaxmize->setChecked(false);
            //TODO
            //Bug：拖动全屏窗口时的不匹配问题

            this->move(e->globalPos());
        } //如果程序被最大化，先恢复正常大小的窗口，然后再继续

        this->move(e->globalPos() - originalPos); //e->globalPos()为鼠标相对于窗口的位置
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isMoveAllowed = false; //禁止窗体移动
}

