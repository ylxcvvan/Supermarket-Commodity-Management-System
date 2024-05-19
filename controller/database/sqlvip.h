#ifndef SQLVIP_H
#define SQLVIP_H
#include <QSqlQuery>
#include <QVariant>
#include"model/vip.h"
namespace SqlVip
{
    //TODO,查询参数待修改
    Vip Query(int id=-1);
    bool insert();
    bool modify();
    bool del();
};

#endif // SQLVIP_H
