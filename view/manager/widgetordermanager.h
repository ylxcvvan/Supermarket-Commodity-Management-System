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
    void loadModel();
    void InitLineEditInputMode();
    void InitBoolSearchState();
private:
    Ui::WidgetOrderManager *ui;
    OrderTableService *p_OrderTableService;

    bool searchOrderId;
    bool searchOrderTime;
    bool searchCashierId;
    bool searchUserId;
    bool searchTotalPrice;
    bool searchPaidPrice;
    bool searchOrderStage;
};

#endif // WIDGETORDERMANAGER_H
