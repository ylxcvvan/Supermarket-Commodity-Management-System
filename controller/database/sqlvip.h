#ifndef SQLVIP_H
#define SQLVIP_H
#include <QSqlQuery>
#include <QVariant>
#include"model/vip.h"
namespace SqlVip
{
QVector<Vip> Query(int id=-1,QString name="" , QString number="",double minpoint=-1,double maxpoint=1e10,int minlevel=-1,int maxlevel=1e10,QDate minrdate=QDate(),QDate maxrdate=QDate());
    bool insert();
    bool modify();
    bool del();
};

#endif // SQLVIP_H
