#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "cashierwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr,bool isadmin=false);
    ~MainWidget();

private slots:
    void on_toolButtonMain_clicked();

private:
    bool isAdmin;

    Ui::MainWidget *ui;
    CashierWidget *pcashiwidget;

};
#endif // MAINWIDGET_H
