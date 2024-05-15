#ifndef SQLCOMMONDITY_H
#define SQLCOMMONDITY_H
#include <QSqlQuery>
#include <QVariant>
#include <QDate>
#include <QVector>
#include "model/commodity.h"
#include "mysql.h"
#include "sqlcommondityitem.h""
namespace SqlCommondity
{

    QVector<Commodity> QueryCommondity(int id=-1,int iid=-1,double p=-1,double cp=-1,QDate sbt=QDate());

};

#endif // SQLCOMMONDITY_H
