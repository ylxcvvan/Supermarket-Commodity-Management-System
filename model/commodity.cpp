#include "commodity.h"

Commodity::Commodity(QString na,double p,double cp,QDate sbt,QString de)
    :Name(na),Price(p),CostPrice(cp),sellByTime(sbt),Details(de){}

const QString &Commodity::getName()
{
    return this->Name;
}

const double &Commodity::getPrice()
{
    return this->Price;
}

const double &Commodity::getcostPrice()
{
    return this->CostPrice;
}

const QString &Commodity::getId()
{
    return this->Id;
}

const QDate &Commodity::getSellByTime()
{
    return this->sellByTime;
}

const QString &Commodity::getDetails()
{
    return this->Details;
}

bool Commodity::setName(const QString &newName)
{
    this->Name=newName;
    return Name==newName;
}

bool Commodity::setPrice(const double &newPrice)
{
    this->Price=newPrice;
    return Price==newPrice;
}

bool Commodity::setDetails(const QString &newDetails)
{
    this->Details=newDetails;
    return Details==newDetails;
}







