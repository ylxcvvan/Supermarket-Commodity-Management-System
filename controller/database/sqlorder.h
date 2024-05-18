#ifndef SQLORDER_H
#define SQLORDER_H
#include <QDateTime>
#include <QSqlQuery>
#include <QVariant>
#include"./model/order.h"

#include<QDebug>

namespace SqlOrder
{
QVector<Order> Query(int orderid=-1,QDateTime orderdate=QDateTime() ,QDateTime orderdateend=QDateTime(),int orderstate=-1,
                            double mintotal=-1,double maxtotal = 1e10,
                            double minpaid=-1,double maxpaid = 1e10,
                            int consumerid=-1,int cashierid=-1);
    bool insert(Order order);
    bool modify();
    bool del();
};

#endif // SQLORDER_H
