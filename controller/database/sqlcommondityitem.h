#ifndef SQLCOMMONDITYITEM_H
#define SQLCOMMONDITYITEM_H
#include"mysqloperate.h"
#include"model/commodityitem.h"

class SqlCommondityItem
{
public:
    SqlCommondityItem();
    //查询商品的itemid,
    QVector<CommodityItem>& QueryCommondityItem();
};

#endif // SQLCOMMONDITYITEM_H
