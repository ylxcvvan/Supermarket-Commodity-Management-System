#include "order.h"

Order::Order(int oid,Glist gl,double tp,double pp,int uid, int cid,state st,QDateTime ti):
    OrderId(oid),
    GoodsList(gl),
    OrderStage(st),
    TotalPrice(tp),
    PaidPrice(pp),
    UserId(uid),
    CashierId(cid),
    OrderTime(ti){}

const int &Order::getOrderId()
{
    return this->OrderId;
}

const Order::Glist &Order::getGoodsList()
{
    return GoodsList;
}


Order::state Order::getOrderStage()
{
    return OrderStage;
}

double Order::getTotalPrice()
{
    return TotalPrice;
}

const int &Order::getUserId()
{
    return UserId;
}

const QDateTime &Order::getOrderTime()
{
    return OrderTime;
}

void Order::setOrderStage(state newOrderStage)
{

    this->OrderStage=newOrderStage;

}




