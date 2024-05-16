#ifndef SQLCOMMONDITYITEM_H
#define SQLCOMMONDITYITEM_H
#include"mysql.h"
#include"model/commodityitem.h"
#include <QSqlQuery>
#include <QVariant>

namespace SqlCommondityItem{

    QVector<CommodityItem> Query(int id=-1,QString name="",QString details="",QString category="");

    //TODO
    bool Del(int id);
    bool Modify(int id , QString newn="", QString newdts="",QString newcate="");//修改id为id 的条目
    bool Insert(QString name="",QString details="",QString category="");
};



#endif // SQLCOMMONDITYITEM_H
