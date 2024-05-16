#include "mainwidget.h"
#include "qpainter.h"
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

void MainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    // 设置边框颜色和宽度
    painter.setPen(QPen(Qt::black, 4));

    // 计算内部矩形的边界
    int borderWidth = 0;
    QRect innerRect(borderWidth, borderWidth, width() - 2 * borderWidth, height() - 2 * borderWidth);

    // 绘制圆润边角的内部矩形
    int radius = 10; // 圆角半径
    painter.drawRoundedRect(innerRect, radius, radius);
}




void MainWidget::FrameLessInit()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    isMoveAllowed=false;
    isFullSceen=false;
}

void MainWidget::on_toolButtonMain_clicked(bool checked)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButtonConfig->setChecked(false);
    ui->toolButtonHelp->setChecked(false);

}

void MainWidget::on_toolButtonHelp_clicked(bool checked)
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButtonMain->setChecked(false);
    ui->toolButtonConfig->setChecked(false);
}


void MainWidget::on_toolButtonConfig_clicked(bool checked)
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->toolButtonHelp->setChecked(false);
    ui->toolButtonMain->setChecked(false);
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
    // 如果鼠标位于窗口边框附近，则允许调整窗口大小
    if (e->x() >= width() - RESIZE_BORDER_WIDTH || e->y() >= height() - RESIZE_BORDER_WIDTH) {
        isResizeAllowed = true;
        setCursor(Qt::CrossCursor);
        originalSize = size();
        resizeRightBottomPoint = e->pos();
        return;
    }
    else if(e->x()<=RESIZE_BORDER_WIDTH||e->y()<=RESIZE_BORDER_WIDTH)
    {
        if (ui->pushButtonMaxmize->isChecked())
            return;
        isResizeAllowed = true;
        setCursor(Qt::CrossCursor);
        originalSize = size();
        resizeRightBottomPoint = QPoint(pos().x()+size().width(),pos().y()+size().height());
        isMoveAllowed=true;
        BeginMovePos = e->pos();
        resizeMinLeftTopPoint=QPoint(resizeRightBottomPoint.x()-this->minimumWidth(),resizeRightBottomPoint.y()-this->minimumHeight());
        return;
    }
    if(e->y() <= ui->widgetTitle->height()+ui->verticalLayout->margin()*1.5){
        isMoveAllowed = true;
        BeginMovePos = e->pos();
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(isMoveAllowed&&isResizeAllowed)
    {
        auto LeftTopPoint=e->globalPos()- BeginMovePos;
        if(LeftTopPoint.x()>resizeMinLeftTopPoint.x()||LeftTopPoint.y()>resizeMinLeftTopPoint.y())
            return;
        this->move(LeftTopPoint);
        int deltaX = resizeRightBottomPoint.x()-LeftTopPoint.x();
        int deltaY = resizeRightBottomPoint.y()-LeftTopPoint.y();
        resize(deltaX, deltaY);
        return;
    }
    else if(isMoveAllowed == true)
    {
        if(ui->pushButtonMaxmize->isChecked()){
            on_pushButtonMaxmize_clicked(false);
            ui->pushButtonMaxmize->setChecked(false);
            //TODO
            //Bug：拖动全屏窗口时的不匹配问题
            BeginMovePos.setX(e->globalX()/2);
        } //如果程序被最大化，先恢复正常大小的窗口，然后再继续
        this->move(e->globalPos() - BeginMovePos); //e->globalPos()为鼠标相对于窗口的位置
    }
    else if (isResizeAllowed)
    {
        if (ui->pushButtonMaxmize->isChecked()) {
            on_pushButtonMaxmize_clicked(false);
            ui->pushButtonMaxmize->setChecked(false);
        }
        int deltaX = e->pos().x() - resizeRightBottomPoint.x();
        int deltaY = e->pos().y() - resizeRightBottomPoint.y();
        resize(originalSize.width() + deltaX, originalSize.height() + deltaY);
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isMoveAllowed = false; //禁止窗体移动
    isResizeAllowed = false;
    setCursor(Qt::ArrowCursor);
}



