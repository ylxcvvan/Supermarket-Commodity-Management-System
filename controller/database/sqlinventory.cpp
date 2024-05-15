#include "sqlinventory.h"
#include "controller/database/sqlcommondity.h"


//库存单号","商品编号","商品名称","商品类别","商品描述",商品数量","商品售价","商品进价","商品保质期",
QVector<QVector<QVariant> > SqlInventory::Query(int id, int cid, QString cname
                                               , QString category, QString details, QDate sellbytime
                                               , double minprice, double maxprice, double mincostprice, double maxcostprice
                                               , double minamount,double maxamount)
{
    QString sql="SELECT * FROM inventory_table WHERE";
    if(id != -1){
        sql+=QString(" Id = %1 AND ").arg(id);
    }
    else if(cid!=-1){
        sql+=QString(" CommodityId = %1 AND ").arg(cid);
    }
    //在这里写数量的范围查询语句

    sql = sql.left(sql.length() - 5)+";";
    qDebug()<<sql;
    //***
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
