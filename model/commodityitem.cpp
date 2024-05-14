#include "commodityitem.h"


CommodityItem::CommodityItem(int iid, QString na, QString de)
    :ItemId(iid),Name(na),Details(de)
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

void CommodityItem::setName(const QString &newname)
{
    this->Name=newname;
}

void CommodityItem::setDetails(const QString &newdetails)
{
    this->Details=newdetails;
}
