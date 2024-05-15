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
    bool Modify();
    bool Insert();
};

#endif // SQLCOMMONDITY_H
