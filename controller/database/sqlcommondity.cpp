#include "sqlcommondity.h"

QVector<Commodity> SqlCommondity::QueryCommondity(int id, int iid, double p, double cp, QDate sbt)
{
    QString sql="SELECT * FROM commodity_table WHERE";
    if(id!=-1){
        sql += QString(" Id = %1 AND ").arg(id);
    }
    if(iid !=-1){
        sql+=QString(" ItemId = %1 AND ").arg(iid);
    }
    if(p != -1){
        sql+=QString(" Price = %1 AND ").arg(p);
    }
    if(cp != -1 ){
        sql+=QString(" CostPrice = %1 AND ").arg(cp);
    }
    if(!sbt.isNull()){
        sql+=QString(" SellByTime = '%1' AND ").arg(sbt.toString("yyyy-MM-dd"));
    }
    sql = sql.left(sql.length() - 5)+";";

    QSqlQuery query=MySql::getInstance().query(sql);
    QVector<Commodity> QueryResult;

    while (query.next())
    {
        QVector<CommodityItem> res = SqlCommondityItem::QueryCommondityItem(query.value(1).toInt());
        Commodity com(query.value(0).toInt(),res.front(),query.value(2).toDouble(),query.value(3).toDouble(),query.value(4).toDate());
        QueryResult.push_back(com);
    }
    for(auto &arr:QueryResult)
    {
        qDebug()<<arr.getId()<<" "<<arr.getName();
    }

    qDebug()<<"________________\n";
    return QueryResult;
}
