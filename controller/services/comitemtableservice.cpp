#include "comitemtableservice.h"
#include "qdebug.h"

ComItemTableService::ComItemTableService() :
    comitemdelegate(new ComItemDelegate)
{
    ItemTableList.resize(12);
    for(auto &p:ItemTableList)
    {
        p=new ComItemTable;
    }
}

ComItemTableService::~ComItemTableService()
{
    for(auto &p:ItemTableList)
    {
        delete p;
    }
    delete comitemdelegate;
     // 释放动态分配的内存
}

ComItemTable *ComItemTableService::getTable(int index)
{
    return ItemTableList[index];
}

void ComItemTableService::setComItemList(int index,QVector<CommodityItem>&&newitem)
{
    qDebug()<<"index:"<<index<<"setlist";
    ItemTableList[index]->setCItemList(std::forward<QVector<CommodityItem>&&>(newitem));
}


ComItemDelegate *ComItemTableService::getComItemDelegate()
{
    return comitemdelegate;
}
