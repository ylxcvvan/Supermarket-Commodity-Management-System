#include "commodity.h"

Commodity::Commodity(CommodityItem cim, double p, double cp, QDate sbt)
    :Name(cim.getName()),Price(p),CostPrice(cp),sellByTime(sbt),Details(cim.getDetails()){}

Commodity::Commodity(QString na,double p,double cp,QDate sbt,QString de)
    :Name(na),Price(p),CostPrice(cp),sellByTime(sbt),Details(de){}

const QString &Commodity::getName() const
{
    return this->Name;
}

const double &Commodity::getPrice() const
{
    return this->Price;
}

const double &Commodity::getcostPrice() const
{
    return this->CostPrice;
}

const QString &Commodity::getId() const
{
    return this->Id;
}

const QDate &Commodity::getSellByTime() const
{
    return this->sellByTime;
}

const QString &Commodity::getDetails() const
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







