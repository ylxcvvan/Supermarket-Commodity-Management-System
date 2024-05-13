#include "order.h"

Order::Order() {}

const QString &Order::getOrderId()
{
    return this->OrderId;
}

const QVector<QPair<Commodity,double>>& Order::getGoodsList()
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

const QString &Order::getUserId()
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




