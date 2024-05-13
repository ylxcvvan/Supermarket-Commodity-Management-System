#include "modelorder.h"

ModelOrder::ModelOrder() {}

const QString &ModelOrder::getOrderId()
{
    return this->OrderId;
}

const QVector<QPair<ModelCommodity,double>>& ModelOrder::getGoodsList()
{
    return GoodsList;
}


ModelOrder::state ModelOrder::getOrderStage()
{
    return OrderStage;
}

double ModelOrder::getTotalPrice()
{
    return TotalPrice;
}

const QString &ModelOrder::getUserId()
{
    return UserId;
}

const QDateTime &ModelOrder::getOrderTime()
{
    return OrderTime;
}

void ModelOrder::setOrderStage(state newOrderStage)
{

    this->OrderStage=newOrderStage;

}




