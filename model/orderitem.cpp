#include "orderitem.h"

OrderItem::OrderItem(int id, int oid, int cid, double camount, double tp)
    :Id(id),OrderId(oid),CommodityId(cid),CommodityAmount(camount),TotalPrice(tp)
{}

int OrderItem::getId() const
{
    return Id;
}

int OrderItem::getOrderId() const
{
    return OrderId;
}

int OrderItem::getCommodityId() const
{
    return CommodityId;
}

double OrderItem::getCommodityAmount() const
{
    return CommodityAmount;
}

double OrderItem::getTotalPrice() const
{
    return TotalPrice;
}
