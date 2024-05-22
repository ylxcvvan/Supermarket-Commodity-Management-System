#include "loginwidget.h"
#include "qevent.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    shadow->setBlurRadius(30);
    //给嵌套QWidget设置阴影
    ui->frame->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    this->setContentsMargins(1,1,1,1);

}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_3_clicked()
{
    this->close();
}

void LoginWidget::mousePressEvent(QMouseEvent *e)
{
    isMoveAllowed = true;
    BeginMovePos = e->pos();
}

void LoginWidget::mouseMoveEvent(QMouseEvent *e)
{
    this->move(e->globalPos() - BeginMovePos); //e->globalPos()为鼠标相对于窗口的位置
}

void LoginWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isMoveAllowed = false; //禁止窗体移动
}


void LoginWidget::on_pushButtonCshierLogin_clicked()
{

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(password.isEmpty()&&username.isEmpty())
    {
        ui->Tips_Column->textlable->setText("请输入用户名和密码");
        ui->Tips_Column->animationStart();
    }
    else if(password.isEmpty())
    {
        ui->Tips_Column->textlable->setText("请输入密码");
        ui->Tips_Column->animationStart();
    }
    else if(username.isEmpty())
    {
        ui->Tips_Column->textlable->setText("请输入用户名");
        ui->Tips_Column->animationStart();
    }
    else
    {
        bool isOk=SqlCashier::login(ui->lineEdit_username->text(),ui->lineEdit_password->text());
        if(isOk)
        {
            MainWidget *w=new MainWidget(nullptr,false);
            w->setUserName(ui->lineEdit_username->text());
            w->show();
            this->close();
        }
        else
        {
            ui->Tips_Column->textlable->setText("用户名或密码错误!");
            ui->Tips_Column->animationStart();
        }
    }

}


void LoginWidget::on_pushButtonAdminLogin_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(password.isEmpty()&&username.isEmpty())
    {
        ui->Tips_Column->textlable->setText("请输入用户名和密码");
        ui->Tips_Column->animationStart();
    }
    else if(password.isEmpty())
    {
        ui->Tips_Column->textlable->setText("请输入密码");
        ui->Tips_Column->animationStart();
    }
    else if(username.isEmpty())
    {
        ui->Tips_Column->textlable->setText("请输入用户名");
        ui->Tips_Column->animationStart();
    }
    else
    {
        bool isOk=SqlAdmin::login(ui->lineEdit_username->text(),ui->lineEdit_password->text());
        if(isOk)
        {
            MainWidget *w=new MainWidget(nullptr,true);
            w->setUserName(ui->lineEdit_username->text());
            w->show();
            this->close();
        }
        else
        {
            ui->Tips_Column->textlable->setText("用户名或密码错误!");
            ui->Tips_Column->animationStart();
        }
    }
}

