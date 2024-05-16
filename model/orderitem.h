#ifndef ORDERITEM_H
#define ORDERITEM_H

class OrderItem
{
private:
    int Id;
    int OrderId;
    int CommodityId;
    double CommodityAmount;
    double TotalPrice;
public:
    OrderItem(int id,int oid,int cid,double camount,double tp);

    int getId() const;
    int getOrderId() const;
    int getCommodityId() const;
    double getCommodityAmount() const;
    double getTotalPrice() const;

};

#endif // ORDERITEM_H
