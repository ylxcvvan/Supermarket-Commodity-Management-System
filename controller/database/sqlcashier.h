#ifndef SQLCASHIER_H
#define SQLCASHIER_H
#include <QSqlQuery>
#include <QVariant>
#include"mysql.h"4
namespace SqlCashier
{
    bool login(QString account,QString password);
};

#endif // SQLCASHIER_H
