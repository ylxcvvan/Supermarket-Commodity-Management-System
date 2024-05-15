#ifndef SQLVIP_H
#define SQLVIP_H
#include <QSqlQuery>
#include <QVariant>
namespace SqlVip
{
    bool Query();
    bool insert();
    bool modify();
    bool del();
};

#endif // SQLVIP_H
