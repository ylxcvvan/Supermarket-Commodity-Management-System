#include "sqlcommondity.h"

QVector<Commodity> SqlCommondity::QueryCommondity(int id, int iid, double p, double cp, QDate sbt)
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
        QVector<CommodityItem> res=SqlCommondityItem::QueryCommondityItem(query.value(1).toInt());
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
