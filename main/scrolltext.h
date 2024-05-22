#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QTime>

class scrolltext : public QWidget
{
    Q_OBJECT
public:
    explicit scrolltext(QWidget *parent = nullptr);
    QLabel *textlable;
    void animationStart();
private:
    QPropertyAnimation *m_TopPropertyAnimation;
signals:

};

#endif // SCROLLTEXT_H
