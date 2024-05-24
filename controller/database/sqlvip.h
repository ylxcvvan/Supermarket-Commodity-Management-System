#ifndef SQLVIP_H
#define SQLVIP_H
#include <QSqlQuery>
#include <QVariant>
#include"model/vip.h"
namespace SqlVip
{
    QVector<Vip> Query(int id=-1,QString name="" , QString number="",double minpoint=-1,double maxpoint=1e5,int minlevel=-1,int maxlevel=1e5,QDate minrdate=QDate(),QDate maxrdate=QDate());
    QVector<Vip> Query(QString number);
    bool insert(QString &name, QString &phone, double point, int level,QDate date=QDate::currentDate());
    bool modify(int id=-1,QString num="",double point=-1,int lev=-1);
    bool del();
};

#endif // SQLVIP_H
