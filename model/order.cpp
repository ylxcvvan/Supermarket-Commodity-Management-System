#include "order.h"

Order::Order(int oid,Glist gl,double tp,double pp,int uid, int cid,stage st,QDateTime ti):
    OrderId(oid),
    GoodsList(gl),
    OrderStage(st),
    TotalPrice(tp),
    PaidPrice(pp),
    UserId(uid),
    CashierId(cid),
    OrderTime(ti){}

const int &Order::getOrderId() const
{
    return this->OrderId;
}

const Order::Glist &Order::getGoodsList() const
{
    return GoodsList;
}


Order::stage Order::getOrderStage() const
{
    return OrderStage;
}

const double& Order::getTotalPrice() const
{
    return TotalPrice;
}

const double& Order::getPaidPrice() const
{
    return PaidPrice;
}

const int &Order::getUserId() const
{
    return UserId;
}

const int &Order::getCashierId() const
{
    return CashierId;
}

const QDateTime &Order::getOrderTime() const
{
    return OrderTime;
}

void Order::setOrderStage(stage newOrderStage)
{

    this->OrderStage=newOrderStage;

}




