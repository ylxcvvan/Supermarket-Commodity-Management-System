#include "modelcommodity.h"

ModelCommodity::ModelCommodity() {}

const QString &ModelCommodity::getName()
{
    return this->Name;
}

const double &ModelCommodity::getPrice()
{
    return this->Price;
}

const double &ModelCommodity::getcostPrice()
{
    return this->CostPrice;
}

const QString &ModelCommodity::getNumber()
{
    return this->Number;
}

const QDate &ModelCommodity::getSellByTime()
{
    return this->sellByTime;
}

const QString &ModelCommodity::getDetails()
{
    return this->Details;
}

int ModelCommodity::getQuantity()
{
    return this->Quantity;
}

bool ModelCommodity::setName(const QString &newName)
{
    this->Name=newName;
    return Name==newName;
}

bool ModelCommodity::setPrice(const double &newPrice)
{
    this->Price=newPrice;
    return Price==newPrice;
}

bool ModelCommodity::setDetails(const QString &newDetails)
{
    this->Details=newDetails;
    return Details==newDetails;
}

void ModelCommodity::setQuantity(const int &newQuantity)
{
    this->Quantity=newQuantity;
}






