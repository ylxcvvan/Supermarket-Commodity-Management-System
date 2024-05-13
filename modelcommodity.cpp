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

const QString &ModelCommodity::getId()
{
    return this->Id;
}

const QDate &ModelCommodity::getSellByTime()
{
    return this->sellByTime;
}

const QString &ModelCommodity::getDetails()
{
    return this->Details;
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







