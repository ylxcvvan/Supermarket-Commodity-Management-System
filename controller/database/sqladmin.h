#ifndef SQLADMIN_H
#define SQLADMIN_H
#include <QSqlQuery>
#include <QVariant>
#include<QString>
#include"mysql.h"
namespace SqlAdmin
{
    bool loginin(QString account,QString password);

};

#endif // SQLADMIN_H
