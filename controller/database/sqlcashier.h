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
    bool updatePassword(QString account, QString newPassword);
    QDateTime queryLastLogintime(QString account); // 声明新的函数
    bool updateLastLoginTime(QString account); // 声明新的函数
};

#endif // SQLCASHIER_H
