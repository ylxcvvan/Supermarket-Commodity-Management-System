#include "modelorder.h"

ModelOrder::ModelOrder() {}

const QString &ModelOrder::getNumber()
{
    return this->Number;
}

QVector<ModelCommodity> ModelOrder::getGoodsList()
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




