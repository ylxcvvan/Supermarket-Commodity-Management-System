#ifndef SQLORDERITEM_H
#define SQLORDERITEM_H
#include <QSqlQuery>
#include <QVariant>
#include<QVector>
#include"./model/orderitem.h"
#include"mysql.h"
#include"./model/orderitem.h"
namespace SqlOrderItem
{
    QVector<OrderItem> Query(int orderid);
    bool insert(int orderid=-1,int comdyid=-1,int amount=-1,double total=-1);
    bool modify();
    bool del();
};

#endif // SQLORDERITEM_H
