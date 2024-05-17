#ifndef ORDER_H
#define ORDER_H
#include<QString>
#include<QDateTime>
#include<QVector>
#include"orderitem.h"
class Order
{
    using Glist=QVector<OrderItem>;
public:
    enum class state {Pending=0,cancelled=1,Completed=2};
private:

    int OrderId;
    //商品，商品数量，总价格计算可得
    Glist GoodsList;
    state OrderStage;
    double TotalPrice;
    double PaidPrice;
    int UserId;
    int CashierId;
    QDateTime OrderTime;

public:

    Order(int oid,Glist gl,double tp,double pp,int uid, int cid,state st=state::Pending,QDateTime ti=QDateTime::currentDateTime());

    const int& getOrderId();
    const Glist& getGoodsList();
    state getOrderStage();
    double getTotalPrice();
    const int& getUserId();
    const QDateTime& getOrderTime();

    void setOrderStage(Order::state newOrderStage);
};

#endif // ORDER_H
