#include "sqlinventory.h"
#include "controller/database/sqlcommondity.h"
#include"mysql.h"

//库存单号","商品编号","商品名称","商品类别","商品描述",商品数量","商品售价","商品进价","商品保质期",
QVector<QVector<QVariant>> SqlInventory::Query(int id, int cid, QString cname ,QString category,QString details,QDate sellbytime
                                               , double minprice, double maxprice, double mincostprice, double maxcostprice
                                               , double minamount,double maxamount)
{
    QString sql = "SELECT * FROM inventory_table WHERE ";
    if(id != -1){
        sql+=QString(" Id = %1 AND ").arg(id);
    }
    if(cid != -1){
        sql += QString(" CommodityId = %1 AND ").arg(cid);
    }
    if(minamount < maxamount){
        sql += QString(" CommodityAmount BETWEEN %1 AND %2 AND ").arg(minamount).arg(maxamount);
    }


    sql = sql.left(sql.length() - 5)+";";
    qDebug()<<sql;
    QSqlQuery query=MySql::getInstance().query(sql);
    QVector<QVector<QVariant>> QueryResult;

    while (query.next())
    {
        auto comVector=SqlCommondity::Query(query.value(1).toInt(),-1,sellbytime,cname,details,category,minprice,maxprice,mincostprice,maxcostprice);
        if(comVector.empty())
            continue;
        Commodity com=comVector.front();
        // qDebug()<<"c";
        QVector<QVariant> result{query.value(0),com.getId(),com.getName(),com.getCategory(),com.getDetails(),query.value(2),com.getPrice(),com.getcostPrice(),com.getSellByTime()};
        QueryResult.push_back(result);
    }

    for(auto& qr:QueryResult)
    {
        qDebug()<<qr[0]<<' '<<qr[1]<<' '<<qr[2]<<' '<<qr[3]<<' '<<qr[4]<<' '<<qr[5].toString().left(5)<<' '<<qr[6];
    }

    return QueryResult;
}

bool SqlInventory::Insert(int condyamount, QString name, double price, double costprice, QDate sbt, QString details, QString category)
{
    SqlCommondity::Insert(name,price,costprice,sbt,details,category);
    auto query =MySql::getInstance().query("SELECT * FROM commodity_table ORDER BY Id DESC LIMIT 1;");
    query.next();
    int comdyid = query.value(0).toInt();
    qDebug()<<comdyid;
    QString sql = QString("INSERT INTO inventory_table (CommodityId,CommodityAmount) "
                          "VALUES(%1,%2);").arg(comdyid).arg(condyamount);
    qDebug()<<sql;
     return MySql::getInstance().modify(sql);
}

bool SqlInventory::sell(int comdyid, int amount)
{
    QString sql = QString("UPDATE inventory_table "
                          "SET CommodityAmount = CommodityAmount - %1 "
                          "WHERE CommodityId = %2 ;").arg(amount).arg(comdyid);
    qDebug()<<sql;
    return MySql::getInstance().modify(sql);
}
