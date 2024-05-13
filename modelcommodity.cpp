#include "modelcommodity.h"

ModelCommodity::ModelCommodity() {}

const QString &ModelCommodity::getName()
{
    return this->name;
}

const double &ModelCommodity::getPrice()
{
    return this->price;
}

const double &ModelCommodity::getcostPrice()
{
    return this->costPrice;
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

bool ModelCommodity::setName(const QString &newName)
{
    this->name=newName;
    return name==newName;
}

bool ModelCommodity::setPrice(const double &newPrice)
{
    this->price=newPrice;
    return price==newPrice;
}

bool ModelCommodity::setDetails(const QString &newDetails)
{
    this->Details=newDetails;
    return Details==newDetails;
}






