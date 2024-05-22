#ifndef SQLCASHIER_H
#define SQLCASHIER_H
#include <QSqlQuery>
#include <QVariant>
#include<model/user.h>
#include"mysql.h"
namespace SqlCashier
{
    bool login(QString account,QString password);
    User query(int id);
    int queryAccount(QString account);
};

#endif // SQLCASHIER_H
