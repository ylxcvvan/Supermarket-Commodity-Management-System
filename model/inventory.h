#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
private:
    int Id;
    int CommodityId;
    double CommodityAmount;
public:
    Inventory(int id,int cid,double amo);

    int getId() const;
    int getCommodityId() const;
    double getCommodityAmount() const;
};

#endif // INVENTORY_H
