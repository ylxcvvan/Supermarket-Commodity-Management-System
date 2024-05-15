#ifndef SQLCOMMONDITYITEM_H
#define SQLCOMMONDITYITEM_H
#include"mysql.h"
#include"model/commodityitem.h"
#include <QSqlQuery>
#include <QVariant>

namespace SqlCommondityItem{

    QVector<CommodityItem> QueryCommondityItem(int id=-1,QString name="",QString details="",QString category="");

    //TODO
    bool Del();
    bool Modify();
    bool Insert();
};



#endif // SQLCOMMONDITYITEM_H
