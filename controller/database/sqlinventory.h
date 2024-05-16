#ifndef SQLINVENTORY_H
#define SQLINVENTORY_H

#include <QSqlQuery>
#include <QVariant>
#include<QDate>
namespace SqlInventory
{

    //库存单号","商品编号","商品名称","商品类别","商品描述",商品数量","商品售价","商品进价","商品保质期",
QVector<QVector<QVariant>> Query(int id=-1,int cid=-1
                                 ,QString cname="",QString category="",QString details="",QDate sellbytime=QDate()
                                ,double minprice=-1,double maxprice=1e10,double mincostprice=-1,double maxcostprice=1e10
                                 ,double minamount=-1,double maxamount=1e10);

    //TODO
    bool Del();
    bool Modify();
    bool Insert(int condyamount=-1,
                QString name="",double price=-1,double costprice=-1,QDate sbt=QDate(),
                QString details="",QString category="");

    bool sell(int comdyid,int amount);
};

#endif // SQLINVENTORY_H
