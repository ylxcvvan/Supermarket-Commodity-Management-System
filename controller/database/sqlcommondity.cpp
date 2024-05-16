#include "sqlcommondity.h"

QVector<Commodity> SqlCommondity::Query(int id, int iid, QDate sbt, QString name, QString details, QString category, double minprice, double maxprice, double mincostprice, double maxcostprice)
{
    QString sql="SELECT * FROM commodity_table WHERE ";
    if(id!=-1){
        sql += QString(" Id = %1 AND ").arg(id);
    }
    if(iid !=-1){
        sql+=QString(" ItemId = %1 AND ").arg(iid);
    }
    if(minprice <= maxprice){
        sql+=QString(" Price between %1 AND %2 AND ").arg(minprice).arg(maxprice);
    }
    if(mincostprice <= maxcostprice){
        sql+=QString(" CostPrice between %1 AND %2 AND ").arg(mincostprice).arg(maxcostprice);
    }
    if(!sbt.isNull()){
        sql+=QString(" SellByTime <'%1' AND ").arg(sbt.toString("yyyy-MM-dd"));
    }
    //在这里增加double minprice, double maxprice, double mincostprice, double maxcostprice的范围查询
    //TODO
    sql = sql.left(sql.length() - 5)+";";
    qDebug()<<sql;
    //**
    QSqlQuery query=MySql::getInstance().query(sql);
    QVector<Commodity> QueryResult;

    while (query.next())
    {
        //*
        qDebug()<<"b";
        QVector<CommodityItem> res=SqlCommondityItem::Query(query.value(1).toInt(),name,details,category);
        if(res.empty())
            continue;
        Commodity com(query.value(0).toInt(),res.front(),query.value(2).toDouble(),query.value(3).toDouble(),query.value(4).toDate());
        QueryResult.push_back(com);
    }
    // for(auto &arr:QueryResult)
    // {
    //     qDebug()<<arr.getId()<<" "<<arr.getName();
    // }
    return QueryResult;
}

bool SqlCommondity::Modify(QString name, double price, double costprice, QDate sbt,
                           QString details, QString category)
{
    //查询商品名为name的itemid；
    QVector<CommodityItem> res = SqlCommondityItem::Query(-1,name,"","");
    int itemid = res[0].getItemId();

    //修改commodityitem表
    SqlCommondityItem::Modify(itemid,"",details,category);
    //修改itemid的信息
    QString sql = "UPDATE commodity_table SET ";
    QStringList updates;

    if (price != -1) {
        updates.append(QString("Price = %1").arg(price));
    }

    if (costprice!=-1) {
        updates.append(QString("Costprice = %1 ").arg(costprice));
    }
    if(!sbt.isNull()){
         updates.append(QString("SellByTime = '%1' ").arg(sbt.toString("yyyy-MM-dd")));
    }
    sql += updates.join(", ");
    sql += QString(" WHERE Item = %1").arg(itemid);

    return MySql::getInstance().modify(sql);
}

bool SqlCommondity::Insert(QString name, double price, double costprice, QDate sbt,
                           QString details, QString category)
{
    QVector<CommodityItem> res = SqlCommondityItem::Query(-1,name,"","");
    if(!res.size()){
        SqlCommondityItem::Insert(name,details,category);
        res = SqlCommondityItem::Query(-1,name,"","");
    }
    int itemid = res[0].getItemId();
    QString sql =QString ("INSERT into commodity_table (INSERT INTO commodity_table "
                          "(ItemId, Price, CostPrice, SellByTime) VALUES(%1,%2,%3,'%4')" )
                            .arg(itemid).arg(price).arg(costprice).arg(sbt.toString("yyyy-MM-dd"));

    return MySql::getInstance().modify(sql);

}


