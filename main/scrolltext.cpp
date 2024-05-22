#include "scrolltext.h"

scrolltext::scrolltext(QWidget *parent) : QWidget(parent)
{
    textlable = new QLabel(this);
    textlable->setStyleSheet("QLabel {\
                             font-family: \"Microsoft YaHei\";\
                             font-size: 18px;\
                             color: red;\
                             font-style: normal;\
                             font-weight: bold;}");
    textlable->setText("This is scrolltext");
    textlable->setFixedHeight(20);
    textlable->hide();

    //文字上移特效
    m_TopPropertyAnimation = new QPropertyAnimation(this,"geometry");
    m_TopPropertyAnimation->setDuration(600);
}

void scrolltext::animationStart()
{
    if(textlable->isHidden())
        textlable->show();
    m_TopPropertyAnimation->setStartValue(QRect(0, textlable->height(), textlable->width(),textlable->height()));
    m_TopPropertyAnimation->setEndValue(QRect(0, 0, textlable->width(),textlable->height()));
    m_TopPropertyAnimation->setEasingCurve(QEasingCurve::OutQuart);
    m_TopPropertyAnimation->start(QAbstractAnimation::KeepWhenStopped);


    QTimer *timer =new QTimer(this);
    timer->start(3000);

    connect(timer,&QTimer::timeout,this,[=]
    {
        m_TopPropertyAnimation->setStartValue(QRect(0,0, textlable->width(),textlable->height()));
        m_TopPropertyAnimation->setEndValue(QRect(0,textlable->height() , textlable->width(),textlable->height()));
        m_TopPropertyAnimation->start(QAbstractAnimation::KeepWhenStopped);
        timer->stop();
        delete timer;
    });

}

