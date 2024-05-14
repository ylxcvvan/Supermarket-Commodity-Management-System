#include "sqlservices.h"

SqlServices::SqlServices()
    :op(new MySqlOperate())
{
}

bool SqlServices::insert_Commodity(const qint64 &id, const qfloat16 &price, const qfloat16 &costprice, const QDate &date)
{
    sql = QString("INSERT INTO commodity_table (ItemId, Price, CostPrice, SellByTime) VALUES (%1,%2,%3,'%4')")
              .arg(id)
              .arg(price)
              .arg(costprice)
              .arg(date.toString("yyyy-MM-dd"));

    if(!op->update(sql)){
        return false;
    }
    return true;

}

bool SqlServices::insert_CommodityItem(const QString &name,const QString &details)
{
    sql = QString("INSERT INTO commodityItem_table (Name, Details) VALUES('%1','%2')")
              .arg(name)
              .arg(details);

    if(!op->update(sql)){
        return false;
    }
    return true;

}

bool SqlServices::insert_Vip(const QString &name, const QString &phonenumber, const qfloat16 &point, const qint64 &level, const QDate &date)
{
    sql = QString("INSERT INTO vip_table (Name, PhoneNumber, Point, Level, RegisterDate) VALUES('%1','%2',%3,%4,'%5')")
              .arg(name).arg(phonenumber).arg(point).arg(level).arg(date.toString("yyyy-MM-dd"));

    if(!op->update(sql)){
        return false;
    }
    return true;

}

bool SqlServices::insert_Inventory(const qint64 &id, const qint64 &commodityid, const qint64 &amount)
{
    sql=QString("INSERT INTO inventory_table (Id, CommodityId, CommodityAmount) VALUES (%1,%2,%3),")
              .arg(id).arg(commodityid).arg(amount);

    if(!op->update(sql)){
        return false;
    }
    return true;

}

bool SqlServices::insert_Order(const QDate &date, const qint64 &state, const qfloat16 &totalprice, const qint64 &consumerid)
{
    sql=QString("INSERT INTO order_table (OrderDate, OrderState, TotalPrice, ConsumerId) VALUES ('%1', %2, %3, %4)")
              .arg(date.toString("yyyy-MM-dd HH:mm:ss"))
              .arg(state)
              .arg(totalprice)
              .arg(consumerid);

    if(!op->update(sql)){
        return false;
    }
    return true;

}

bool SqlServices::insert_OrderItem(const qint64 &orderid, const qint64 &commodityid, const qint64 &amount, const qfloat16 &totalprice)
{
    sql = QString("INSERT INTO orderItem_table (OrderId, CommodityId, CommodityAmount, TotalPrice)VALUES (%1, %2,%3, %4)")
              .arg(orderid)
              .arg(commodityid)
              .arg(amount)
              .arg(totalprice);

    if(!op->update(sql)){
        return false;
    }
    return true;

}
