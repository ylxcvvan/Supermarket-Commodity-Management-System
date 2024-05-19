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

        sql += QString(" Details LIKE '%%1%' AND ").arg(details);
    }
    if(!category.isEmpty()){

        sql+=QString(" Category LIKE '%%1%' AND ").arg(category);
    }
    // 移除最后的 AND
    sql = sql.left(sql.length() - 5)+";";
    qDebug()<<sql<<"";
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



bool SqlCommondityItem::Del(int id)
{
    QString sql = QString(" DELETE FROM commodityitem_table WHERE Id = %1 ;").arg(id);
        qDebug()<<sql;
    return MySql::getInstance().modify(sql);
}

bool SqlCommondityItem::Insert(QString name, QString details, QString category)
{
    QString sql = QString(" INSERT INTO commodityItem_table (Name,Details,Category) "
                          " VALUES ('%1','%2','3');").arg(name).arg(details).arg(category);
        qDebug()<<sql;

    return MySql::getInstance().modify(sql);
}


bool SqlCommondityItem::Modify(int id, QString newn, QString newdts, QString newcate)
{
    QString sql = "UPDATE commodityitem_table SET ";
    QStringList updates;

    if (!newn.isEmpty()) {
        updates.append(QString("Name = '%1'").arg(newn));
    }

    if (!newdts.isEmpty()) {
        updates.append(QString("Details = '%1'").arg(newdts));
    }

    if (!newcate.isEmpty()) {
        updates.append(QString("Category = '%1'").arg(newcate));
    }

    if (updates.isEmpty()) {
        // 如果没有需要更新的字段，则直接返回
        qDebug()<<"商品信息不需要更新";
        return false;
    }

    sql += updates.join(", ");
    sql += QString(" WHERE id = %1").arg(id);
        qDebug()<<sql;
    return MySql::getInstance().modify(sql);
}
