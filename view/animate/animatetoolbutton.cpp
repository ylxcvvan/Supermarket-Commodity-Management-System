// #include "animatetoolbutton.h"
// #include "qdebug.h"
// #include "qstyleoption.h"



// AnimateToolButton::AnimateToolButton(QWidget *parent) :
//     QToolButton(parent),
//     m_previousSize(this->size()), // 记录动画之前的按钮大小
// {
//     setCheckable(true); // 设置按钮为可检查状态

//     // 设置默认的起始值和结束值
//     m_animation.setTargetObject(this);
//     m_animation.setPropertyName("size");
//     m_animation.setStartValue(QSize(200, 200)); // 起始大小
//     m_animation.setEndValue(QSize(220, 220));   // 结束大小
//     m_animation.setDuration(200);              // 持续时间

//     // 连接动画的信号和槽
//     connect(&m_animation, &QPropertyAnimation::finished, this, &AnimateToolButton::onAnimationFinished);
//     connect(this, &QToolButton::clicked, this, &AnimateToolButton::startAnimation);
// }

// void AnimateToolButton::nextCheckState()
// {
//     // 在状态变化时调用动画
//     QToolButton::nextCheckState();
//     startAnimation();
// }

// void AnimateToolButton::startAnimation()
// {
//     m_animation.stop();
//     m_animation.start();

// }

// void AnimateToolButton::onAnimationFinished()
// {
//     // 在动画结束后设置按钮的大小
//     setFixedSize(m_previousSize);
// }
