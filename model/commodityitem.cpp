#include "commodityitem.h"


CommodityItem::CommodityItem()
{

}

CommodityItem::CommodityItem(int iid, QString na, QString de,QString ca)
    :ItemId(iid),Name(na),Details(de),Category(ca)
{

}

int CommodityItem::getItemId() const
{
    return ItemId;
}

QString CommodityItem::getName() const
{
    return Name;
}

QString CommodityItem::getDetails() const
{
    return Details;
}

QString CommodityItem::getCategory() const
{
    return Category;
}

void CommodityItem::setName(const QString &newname)
{
    this->Name=newname;
}

void CommodityItem::setDetails(const QString &newdetails)
{
    this->Details=newdetails;
}

void CommodityItem::setCategory(const QString &newcategory)
{
    this->Category=newcategory;
}
