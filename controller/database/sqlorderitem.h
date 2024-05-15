#ifndef SQLORDERITEM_H
#define SQLORDERITEM_H
#include <QSqlQuery>
#include <QVariant>
namespace SqlOrderItem
{
    bool Query();
    bool insert();
    bool modify();
    bool del();
};

#endif // SQLORDERITEM_H
