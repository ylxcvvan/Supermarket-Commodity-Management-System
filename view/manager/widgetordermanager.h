#ifndef WIDGETORDERMANAGER_H
#define WIDGETORDERMANAGER_H

#include <QWidget>
#include"controller/services/ordertableservice.h"
namespace Ui {
class WidgetOrderManager;
}

class WidgetOrderManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetOrderManager(QWidget *parent = nullptr);
    ~WidgetOrderManager();
    void InitBoolSearchState();
    void loadModelOrder();
private:
    void InitLineEditInputMode();

private slots:
    void on_pushButtonOrderId_clicked(bool checked);

    void on_pushButtonOrderStage_clicked(bool checked);

    void on_pushButtonCashierId_clicked(bool checked);

    void on_pushButtonUserId_clicked(bool checked);

    void on_pushButtonOrderTime_clicked(bool checked);

    void on_pushButtonTotalPrice_clicked(bool checked);

private:
    Ui::WidgetOrderManager *ui;
    OrderTableService *p_OrderTableService;

    bool searchOrderId=false;
    bool searchOrderTime=false;
    bool searchCashierId=false;
    bool searchUserId=false;
    bool searchOrderStage=false;
    bool searchTotalPrice=false;
};

#endif // WIDGETORDERMANAGER_H
