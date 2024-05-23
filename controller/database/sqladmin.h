#ifndef SQLADMIN_H
#define SQLADMIN_H
#include <QSqlQuery>
#include <QVariant>
#include<QString>
#include"mysql.h"
namespace SqlAdmin
{
    bool login(QString account,QString password);
    bool updatePassword(QString account, QString newPassword);
    QDateTime queryLastLogintime(QString account);
    bool updateLastLoginTime(QString account);

};

#endif // SQLADMIN_H
