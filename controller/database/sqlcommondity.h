#ifndef SQLCOMMONDITY_H
#define SQLCOMMONDITY_H
#include <QSqlQuery>
#include <QVariant>
#include <QDate>
#include <QVector>
#include "model/commodity.h"
#include "mysql.h"
#include "sqlcommondityitem.h""
namespace SqlCommondity
{

    QVector<Commodity> Query(int id=-1,int iid=-1,QDate sbt=QDate(),
                        QString name="",QString details="",QString category="",
                         double minprice=-1,double maxprice=1e10,double mincostprice=-1,double maxcostprice=1e10);

    //TODO
    bool Del();
    //修改商品名为name的商品的其他信息；
    bool Modify(QString name,double price=-1,double costprice=-1,QDate sbt=QDate(),
                QString details="",QString category=""  );
    //插入商品
    bool Insert(QString name,double price=-1,double costprice=-1,QDate sbt=QDate(),
                QString details="",QString category=""  );

};

#endif // SQLCOMMONDITY_H
