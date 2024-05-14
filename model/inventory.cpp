#include "inventory.h"

Inventory::Inventory(int id, int cid, double amo)
    :Id(id),CommodityId(cid),CommodityAmount(amo)
{}

int Inventory::getId() const
{
    return Id;
}

int Inventory::getCommodityId() const
{
    return CommodityId;
}

double Inventory::getCommodityAmount() const
{
    return CommodityAmount;
}
