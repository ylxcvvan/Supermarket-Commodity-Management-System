#include "commodity.h"

Commodity::Commodity(int id,CommodityItem cim, double p, double cp, QDate sbt)
    :Id(id),Name(cim.getName()),Price(p),CostPrice(cp),sellByTime(sbt),Details(cim.getDetails()){}

Commodity::Commodity(int id,QString na,double p,double cp,QDate sbt,QString de)
    :Id(id),Name(na),Price(p),CostPrice(cp),sellByTime(sbt),Details(de){}

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

int Commodity::getId() const
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







