#include "sqlcommondityitem.h"
#include<QDebug>



QVector<CommodityItem> SqlCommondityItem::Query(int id, QString name, QString details,QString category)
{
    QString sql = "SELECT * FROM commodityItem_table WHERE";
    if (id != -1) {

        sql += QString(" Id = %1 AND ").arg(id);
    }
    if (!name.isEmpty()) {

        sql += QString(" Name LIKE '%%1%' AND ").arg(name);
    }
    if (!details.isEmpty()) {

        sql += QString("Details LIKE '%%1%' AND ").arg(details);
    }
    if(!category.isEmpty()){

        sql+=QString("Category LIKE '%%1%' AND ").arg(category);
    }
    // 移除最后的 AND
    sql = sql.left(sql.length() - 5)+";";
    qDebug()<<sql;
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


    return QueryResult;
}
