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
    Q_PROPERTY(QSize buttonSize READ buttonSize WRITE setButtonSize)
public:
    AnimateToolButton(QWidget *parent = nullptr);

    qreal fillRatio() const;
    void setFillRatio(qreal ratio);

    QSize buttonSize() const;
    void setButtonSize(const QSize &size);

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void paintEvent(QPaintEvent *event) override;


private slots:
    void onAnimationFinished();

private:
    QPropertyAnimation m_fillAnimation;
    QPropertyAnimation m_scaleAnimation;
    qreal m_fillRatio;
    QSize m_buttonSize;
    void startAnimate(qreal endvalue,QSize endsize);
};

#endif // BUTTONANIMATEHELPER_H
