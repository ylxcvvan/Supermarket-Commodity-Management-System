#include "sqlcommondity.h"

QVector<Commodity> SqlCommondity::Query(int id, int iid, QDate sbt, QString name, QString details, QString category, double minprice, double maxprice, double mincostprice, double maxcostprice)
{
    QString sql="SELECT * FROM commodity_table WHERE ";
    //TODO
    if(id!=-1)
        sql+=QObject::tr("Id = %1 AND ").arg(id);
    sql = sql.left(sql.length() - 5)+";";

    QSqlQuery query=MySql::getInstance().query(sql);
    QVector<Commodity> QueryResult;

    while (query.next())
    {
        QVector<CommodityItem> res=SqlCommondityItem::Query(query.value(1).toInt(),name,details,category);
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
