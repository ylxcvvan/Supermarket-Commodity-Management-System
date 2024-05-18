#ifndef PAGEMAIN_H
#define PAGEMAIN_H

#include <QWidget>
#include "qtoolbutton.h"
#include"resizableiconbutton.h"
#include"view/manager/widgetcashiermanager.h"
#include"view/manager/widgetinventorymanager.h"
#include"view/manager/widgetordermanager.h"
#include"view/manager/widgetvipmanager.h"
namespace Ui {
class PageMain;
}

class PageMain : public QWidget
{
    Q_OBJECT

public:
    explicit PageMain(QWidget *parent = nullptr,bool isAdmin=false);
    ~PageMain();

private:
    void setOtherWidgetUnchecked(int index);

private slots:

    void on_toolButtonCashier_clicked();

    void on_toolButtonInventory_clicked();

    void on_toolButtonOrder_clicked();

    void on_toolButtonVip_clicked();

private:
    Ui::PageMain *ui;
    QVector<QWidget*> widgetVec;
    QVector<QToolButton*>toolbtnVec;

    WidgetCashierManager *p_widgetCashier;
    WidgetInventoryManager *p_widgetInventory;
    WidgetOrderManager *p_widgetOrder;
    WidgetVipManager *p_widgetVip;

};

#endif // PAGEMAIN_H
