#ifndef BUTTONANIMATEHELPER_H
#define BUTTONANIMATEHELPER_H

#include "qpushbutton.h"
#include <QApplication>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QEvent>
#include <QPainter>
#include <QWidget>

class AnimateToolButton:  public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(qreal fillRatio READ fillRatio WRITE setFillRatio)
public:
    AnimateToolButton(QWidget *parent = nullptr);

    qreal fillRatio() const;
    void setFillRatio(qreal ratio);

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onAnimationFinished();
private:
    QPropertyAnimation m_animation;
    qreal m_fillRatio;

    void startAnimate(double endvalue);
};

#endif // BUTTONANIMATEHELPER_H
