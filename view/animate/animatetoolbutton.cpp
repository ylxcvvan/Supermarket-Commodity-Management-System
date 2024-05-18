#include "animatetoolbutton.h"
#include "qdebug.h"
#include "qstyleoption.h"



AnimateToolButton::AnimateToolButton(QWidget *parent) :
    QToolButton(parent),
    m_fillRatio(0.0)
{
    setMouseTracking(true);
    m_animation.setTargetObject(this);
    m_animation.setPropertyName("fillRatio");
    m_animation.setDuration(500); // 持续时间

    // 确保动画在鼠标离开时回到起点
    connect(&m_animation, &QPropertyAnimation::finished, this, &AnimateToolButton::onAnimationFinished);

}

qreal AnimateToolButton::fillRatio() const {
    return m_fillRatio;
}

void AnimateToolButton::setFillRatio(qreal ratio)
{
    m_fillRatio = ratio;
    update(); // 触发重绘
}



void AnimateToolButton::enterEvent(QEvent *event)
{
    qDebug()<<"enter";
    startAnimate(1.0);
    QToolButton::enterEvent(event);
}

void AnimateToolButton::leaveEvent(QEvent *event)
{
     qDebug()<<"leave";
    startAnimate(0.0);
    QToolButton::leaveEvent(event);
}

void AnimateToolButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 创建渐变
    QLinearGradient gradient( 0, height() * (1 - m_fillRatio),0,height());
    gradient.setColorAt(0, QColor(0, 0, 0, 0));
    gradient.setColorAt(1, QColor(0, 0, 255, 100)); // 蓝色不透明

    painter.fillRect(rect(), gradient);
}

void AnimateToolButton::onAnimationFinished()
{
    // 动画完成后的处理
    if (m_animation.direction() == QPropertyAnimation::Backward)
    {
        setFillRatio(0.0); // 恢复初始状态
    }
}

void AnimateToolButton::startAnimate(double endvalue)
{
    m_animation.stop();
    m_animation.setStartValue(m_fillRatio);
    m_animation.setEndValue(endvalue);
    m_animation.start();
}

