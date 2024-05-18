#include "animatetoolbutton.h"
#include "qdebug.h"
#include "qstyleoption.h"



AnimateToolButton::AnimateToolButton(QWidget *parent) :
    QToolButton(parent),
    m_fillAnimation(this,"fillRatio"),
    m_scaleAnimation(this,"buttonSize"),
    m_fillRatio(0.0),
    m_buttonSize(size())
{
    setMouseTracking(true);
    m_fillAnimation.setTargetObject(this);
    m_fillAnimation.setDuration(200); // 持续时间


    m_scaleAnimation.setDuration(200); // 持续时间


    // 确保动画在鼠标离开时回到起点
    connect(&m_fillAnimation, &QPropertyAnimation::finished, this, &AnimateToolButton::onAnimationFinished);

}

qreal AnimateToolButton::fillRatio() const {
    return m_fillRatio;
}

void AnimateToolButton::setFillRatio(qreal ratio)
{
    m_fillRatio = ratio;
    update(); // 触发重绘
}

QSize AnimateToolButton::buttonSize() const {
    return m_buttonSize;
}

void AnimateToolButton::setButtonSize(const QSize &size)
{
    m_buttonSize = size;
    setFixedSize(size);
}

void AnimateToolButton::enterEvent(QEvent *event)
{

    startFillAnimate(1.0);
    startScaleAnimate(size()*10/9);

    QToolButton::enterEvent(event);
}

void AnimateToolButton::leaveEvent(QEvent *event)
{

    startFillAnimate(0.0);
    startScaleAnimate(size()*9/10);
    QToolButton::leaveEvent(event);
}

void AnimateToolButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event); // 先调用父类的绘制函数

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 创建渐变
    QLinearGradient gradient(0, height() * (1 - m_fillRatio), 0, height());
    gradient.setColorAt(0, QColor(0, 0, 0, 0)); // 起始颜色透明
    gradient.setColorAt(1, QColor(0, 0, 255, 100)); // 蓝色半透明
    painter.fillRect(rect(), gradient);
}

void AnimateToolButton::onAnimationFinished()
{
    // 动画完成后的处理
    if (m_fillAnimation.direction() == QPropertyAnimation::Backward)
    {
        setFillRatio(0.0); // 恢复初始状态
    }
    if(m_scaleAnimation.direction() == QPropertyAnimation::Backward)
    {
        setButtonSize(m_buttonSize);
    }
}

void AnimateToolButton::startFillAnimate(qreal endvalue)
{
    m_fillAnimation.stop();
    m_fillAnimation.setStartValue(m_fillRatio);
    m_fillAnimation.setEndValue(endvalue);
    m_fillAnimation.start();
}

void AnimateToolButton::startScaleAnimate(QSize endsize)
{
    qDebug()<<endsize;
    // 设置大小动画
    m_scaleAnimation.stop(); // 停止之前的动画
    m_scaleAnimation.setStartValue(size());
    m_scaleAnimation.setEndValue(endsize);
    m_scaleAnimation.start();
}

