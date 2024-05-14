#ifndef COMMODITYITEM_H
#define COMMODITYITEM_H
#include<QString>
class CommodityItem
{
private:
    int ItemId;
    QString Name;
    QString Details;

public:
    CommodityItem(int iid,QString na,QString de="该商品没有描述");
    int getItemId() const;
    QString getName() const;
    QString getDetails() const;

    void setName(const QString& newname);
    void setDetails(const QString& newdetails);
};

#endif // COMMODITYITEM_H
