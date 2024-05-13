#ifndef WIDGETCASHIERMANAGER_H
#define WIDGETCASHIERMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
namespace Ui {
class WidgetCashierManager;
}

class WidgetCashierManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCashierManager(QWidget *parent = nullptr);
    ~WidgetCashierManager();

private:
    Ui::WidgetCashierManager *ui;
    QStandardItemModel* cashier_standard_model;
    QTableView* cashier_table_view;
};

#endif // WIDGETCASHIERMANAGER_H
