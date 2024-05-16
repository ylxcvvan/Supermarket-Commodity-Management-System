#include "sqlorderitem.h"

QVector<OrderItem> SqlOrderItem::Query(int orderid)
{
    QString sql = QString("SELECT * FROM orderitem_table WHERE id = %1").arg(orderid);
    qDebug()<<sql;
    QSqlQuery query = MySql::getInstance().query(sql);

    QVector<OrderItem> orderitems;
    while(query.next()){
        OrderItem item = OrderItem(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),
                                   query.value(3).toInt(),query.value(4).toInt());

        orderitems.push_back(item);
    }

    return orderitems;
}

bool SqlOrderItem::insert(int orderid, int comdyid, int amount, double total)
{
    QString sql = QString("INSERT INTO orderitem_table(OrderId,CommodityId,CommodityAmount,TotalPrice) VALUES"
                          "(%1,%2,%3,%4)").arg(orderid).arg(comdyid).arg(amount).arg(total);

    qDebug()<<sql;

    return MySql::getInstance().modify(sql);
}
