#ifndef MODELORDER_H
#define MODELORDER_H
#include<QString>
#include<QDateTime>
#include<QVector>
#include"modelcommodity.h"
class ModelOrder
{
private:
    enum state{Pending=0,cancelled=1,Completed=2};
    QString OrderId;
    QVector<QPair<ModelCommodity,double>>GoodsList;
    state OrderStage;
    double TotalPrice;
    QString UserId;
    QDateTime OrderTime;

public:
    ModelOrder();

    const QString& getOrderId();
    const QVector<QPair<ModelCommodity,double>>& getGoodsList();
    state getOrderStage();
    double getTotalPrice();
    const QString& getUserId();
    const QDateTime& getOrderTime();

    void setOrderStage(ModelOrder::state newOrderStage);
};

#endif // MODELORDER_H
