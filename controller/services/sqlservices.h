#ifndef SQLSERVICES_H
#define SQLSERVICES_H

#include"./controller/database/mysqloperate.h"
#include<QFloat16>
#include<QDate>
class SqlServices
{
public:
    SqlServices();

    bool insert_Commodity(const qint64& id,const qfloat16& price,const qfloat16& costprice,const QDate & date);//狭义的商品
    bool insert_CommodityItem(const QString& name,const QString& details);//广义的商品

    bool insert_Vip(const QString& name,const QString& phonenumber,const qfloat16& point,const qint64& level,const QDate& date);//会员
    bool insert_Inventory(const qint64& id,const qint64& commodityid,const qint64& amount);//仓库

    bool insert_Order(const QDate& date,const qint64& state,const qfloat16& totalprice,const qint64& consumerid);//订单
    bool insert_OrderItem(const qint64& orderid,const qint64& commodityid,const qint64& amount,const qfloat16& totalprice);//订单包含的物品

private:
    QString sql;
    MySqlOperate *op;
};

#endif // SQLSERVICES_H
