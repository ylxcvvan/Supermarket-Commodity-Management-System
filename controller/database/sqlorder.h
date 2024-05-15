#ifndef SQLORDER_H
#define SQLORDER_H
#include <QSqlQuery>
#include <QVariant>
namespace SqlOrder
{
    bool Query();
    bool insert();
    bool modify();
    bool del();
};

#endif // SQLORDER_H
