#include "sqlinventory.h"
#include "controller/database/sqlcommondity.h"

//库存单号","商品编号","商品名称","商品类别","商品描述",商品数量","商品售价","商品进价","商品保质期",
QVector<QVector<QVariant> > SqlInventory::Query(int id, int cid, double camount, QString cname
                                               , QString category, QString Details, QDate sellbytime
                                               , double minprice, double maxprice, double mincostprice, double maxcostprice)
{
    QString sql="SELECT * FROM inventory_table;";
    //TODO

    QSqlQuery query=MySql::getInstance().query(sql);
    QVector<QVector<QVariant>> QueryResult;

    while (query.next())
    {
        //TODO
        Commodity com=SqlCommondity::Query(query.value(1).toInt()).front();

        QVector<QVariant> result{query.value(0),com.getId(),com.getName(),com.getCategory(),com.getDetails(),query.value(2),com.getPrice(),com.getcostPrice(),com.getSellByTime()};
        QueryResult.push_back(result);
    }
    qDebug()<<sql;
    for(auto& qr:QueryResult)
    {
        qDebug()<<qr[0]<<' '<<qr[1]<<' '<<qr[2]<<' '<<qr[3]<<' '<<qr[4]<<' '<<qr[5].toString().left(5)<<' '<<qr[6];
    }

    return QueryResult;
}
