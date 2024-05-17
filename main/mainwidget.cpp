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

void MainWidget::FrameLessInit()
{
    setWindowFlags(Qt::FramelessWindowHint);

    isMoveAllowed=false;
    isFullSceen=false;

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // 创建一个QGraphicsDropShadowEffect对象
    shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor(0, 0, 0, 160)); // 黑色阴影，透明度为160
    shadowEffect->setBlurRadius(20); // 阴影模糊半径
    this->layout()->QLayout::setContentsMargins(layoutmargin,layoutmargin,layoutmargin,layoutmargin);
    // 将阴影效果应用到整个窗口
    ui->frame->setGraphicsEffect(shadowEffect);

    shadowEffect_2 = new QGraphicsDropShadowEffect(this);
    shadowEffect_2->setOffset(0, 0);
    shadowEffect_2->setColor(QColor(0, 0, 0, 160)); // 黑色阴影，透明度为160
    shadowEffect_2->setBlurRadius(20); // 阴影模糊半径
    this->layout()->QLayout::setContentsMargins(layoutmargin,layoutmargin,layoutmargin,layoutmargin);
    // 将阴影效果应用到整个窗口
    ui->frame_2->setGraphicsEffect(shadowEffect_2);
}

void MainWidget::on_toolButtonMain_clicked(bool checked)
{
    if(ui->stackedWidget->isHidden()) {
        ui->stackedWidget->show();
        update(); // 刷新窗口绘图
    } else if(ui->stackedWidget->currentIndex() == 0) {
        ui->stackedWidget->hide();
        ui->toolButtonMain->setChecked(false);
        update(); // 刷新窗口绘图
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButtonConfig->setChecked(false);
    ui->toolButtonHelp->setChecked(false);

}

void MainWidget::on_toolButtonConfig_clicked(bool checked)
{
    if(ui->stackedWidget->isHidden()) {
        ui->stackedWidget->show();
        update(); // 刷新窗口绘图
    } else if(ui->stackedWidget->currentIndex() == 1) {
        ui->stackedWidget->hide();
        ui->toolButtonConfig->setChecked(false);
        update(); // 刷新窗口绘图
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButtonHelp->setChecked(false);
    ui->toolButtonMain->setChecked(false);
}

void MainWidget::on_toolButtonHelp_clicked(bool checked)
{
    if(ui->stackedWidget->isHidden()) {
        ui->stackedWidget->show();
        update(); // 刷新窗口绘图
    } else if(ui->stackedWidget->currentIndex() == 2) {
        ui->stackedWidget->hide();
        ui->toolButtonHelp->setChecked(false);
        update(); // 刷新窗口绘图
    }
    ui->stackedWidget->setCurrentIndex(2);
    ui->toolButtonMain->setChecked(false);
    ui->toolButtonConfig->setChecked(false);
}

void MainWidget::on_pushButtonMinmize_clicked()
{
    this->showMinimized();
}

void MainWidget::on_pushButtonMaxmize_clicked(bool checked)
{
    if (checked) {
        qDebug()<< this->layout()->contentsMargins();
        this->layout()->QLayout::setContentsMargins(0,0,0,0);
        this->showMaximized();
    } else {
        this->layout()->QLayout::setContentsMargins(layoutmargin,layoutmargin,layoutmargin,layoutmargin);
        this->showNormal();
    }
    this->update();
}



void MainWidget::on_pushButtonExit_clicked()
{
    QApplication::quit();
}

Qt::CursorShape MainWidget::getResizeCursor(bool r,bool b,bool l,bool t)
{
    if ((r && t)||(l && b))
        return Qt::SizeBDiagCursor;
    else if((r && b)||(l && t))
        return Qt::SizeFDiagCursor;
    else if (r||l)
        return Qt::SizeHorCursor;
    else if (b||t)
        return Qt::SizeVerCursor;
    else
        return Qt::ArrowCursor;
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    //获取鼠标所在的位置是在窗口的哪个边界
    bool e_rightborder=e->x() >= width() - RESIZE_BORDER_WIDTH;
    bool e_bottomborder=e->y() >= height() - RESIZE_BORDER_WIDTH;
    bool e_leftborder=e->x()<=RESIZE_BORDER_WIDTH;
    bool e_topborder=e->y()<=RESIZE_BORDER_WIDTH-5;
    setCursor(getResizeCursor(e_rightborder,e_bottomborder,e_leftborder,e_topborder));

    if (e_rightborder || e_bottomborder) {
        isResizeAllowed = true;
        originalSize = size();
        resizeRightBottomPoint = e->pos();
        return;
    }
    else if(e_leftborder||e_topborder)
    {
        if (ui->pushButtonMaxmize->isChecked())
            return;
        isResizeAllowed = true;
        originalSize = size();
        resizeRightBottomPoint = QPoint(pos().x()+size().width(),pos().y()+size().height());
        isMoveAllowed=true;
        BeginMovePos = e->pos();
        resizeMinLeftTopPoint=QPoint(resizeRightBottomPoint.x()-this->minimumWidth(),resizeRightBottomPoint.y()-this->minimumHeight());
        return;
    }//
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
        if(LeftTopPoint.x()>resizeMinLeftTopPoint.x())
        {
            LeftTopPoint.setX(resizeMinLeftTopPoint.x());
        }
        if(LeftTopPoint.y()>resizeMinLeftTopPoint.y())
        {
            LeftTopPoint.setY(resizeMinLeftTopPoint.y());
        }
        this->move(LeftTopPoint);
        int deltaX = resizeRightBottomPoint.x()-LeftTopPoint.x();
        int deltaY = resizeRightBottomPoint.y()-LeftTopPoint.y();
        resize(deltaX, deltaY);
    }
    else if(isMoveAllowed == true)
    {
        if(ui->pushButtonMaxmize->isChecked()){
            on_pushButtonMaxmize_clicked(false);
            ui->pushButtonMaxmize->setChecked(false);
            //解决拖动全屏窗口时的不匹配问题
            BeginMovePos.setX(e->globalX()/2);
        }
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



