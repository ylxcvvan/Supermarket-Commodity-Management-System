#ifndef SQLVIP_H
#define SQLVIP_H
#include <QSqlQuery>
#include <QVariant>
#include"model/vip.h"
namespace SqlVip
{
    Vip Query(QString number);
    bool insert();
    bool modify();
    bool del();
};

#endif // SQLVIP_H
