#ifndef ORDER_H
#define ORDER_H
#include<QString>
#include<QDateTime>
#include<QVector>
#include"commodity.h"
class Order
{
    using Glist=QVector<QPair<Commodity,double>>;
private:
    enum state{Pending=0,cancelled=1,Completed=2};
    int OrderId;
    //商品，商品数量，总价格计算可得
    Glist GoodsList;
    state OrderStage;
    double TotalPrice;
    int UserId;
    QDateTime OrderTime;

public:
    Order(int oid,Glist gl,double tp,int uid,state st=state::Pending,QDateTime ti=QDateTime::currentDateTime());

    const int& getOrderId();
    const Glist& getGoodsList();
    state getOrderStage();
    double getTotalPrice();
    const int& getUserId();
    const QDateTime& getOrderTime();

    void setOrderStage(Order::state newOrderStage);
};

#endif // ORDER_H
