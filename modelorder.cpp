#include "modelorder.h"

ModelOrder::ModelOrder() {}

const QString &ModelOrder::getNumber()
{
    return this->Number;
}

const QVector<ModelOrder> &ModelOrder::getGoodsList()
{
    return this->GoodsList;
}

ModelOrder::state ModelOrder::getOrderStage()
{
    return OrderStage;
}

double ModelOrder::getTotalPrice()
{
    return TotalPrice;
}

const QString &ModelOrder::getPhoneNumber()
{
    return PhoneNumber;
}

const QDateTime &ModelOrder::getOrderTime()
{
    return OrderTime;
}

void ModelOrder::setOrderStage(state newOrderStage)
{

    this->OrderStage=newOrderStage;

}




