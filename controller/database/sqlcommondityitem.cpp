#include "sqlcommondityitem.h"
#include<QDebug>


QVector<CommodityItem> SqlCommondityItem::QueryCommondityItem(int id, QString name, QString details,QString category)
{
    QString sql = "SELECT * FROM commodityItem_table WHERE";
    if (id != -1) {
        sql += QObject::tr(" Id = %1 AND ").arg(id);
    }
    if (!name.isEmpty()) {
        sql += " Name LIKE "+name+" AND ";
    }
    if (!details.isEmpty()) {
        sql += "Details LIKE "+details+" AND ";
    }
    if(!category.isEmpty()){
        sql+="details LIKE "+details+" AND ";
    }
    // 移除最后的 AND
    sql = sql.left(sql.length() - 5)+";";

    QSqlQuery query=MySql::getInstance().query(sql);
    QVector<CommodityItem> QueryResult;

    while (query.next())
    {
        CommodityItem result(query.value(0).toInt()
                             ,query.value(1).toString()
                             ,query.value(2).toString()
                             ,query.value(3).toString());
        QueryResult.push_back(result);
    }
    for(auto &arr:QueryResult)
    {
        qDebug()<<arr.getItemId()<<arr.getName()<<arr.getDetails()<<arr.getCategory();
    }
    qDebug()<<sql;
    qDebug()<<"item_______________\n";
    return QueryResult;
}
