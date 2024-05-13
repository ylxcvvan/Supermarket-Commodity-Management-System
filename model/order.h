#ifndef ORDER_H
#define ORDER_H
#include<QString>
#include<QDateTime>
#include<QVector>
#include"commodity.h"
class Order
{
private:
    enum state{Pending=0,cancelled=1,Completed=2};
    QString OrderId;
    QVector<QPair<Commodity,double>>GoodsList;
    state OrderStage;
    double TotalPrice;
    QString UserId;
    QDateTime OrderTime;

public:
    Order();

    const QString& getOrderId();
    const QVector<QPair<Commodity,double>>& getGoodsList();
    state getOrderStage();
    double getTotalPrice();
    const QString& getUserId();
    const QDateTime& getOrderTime();

    void setOrderStage(Order::state newOrderStage);
};

#endif // ORDER_H
