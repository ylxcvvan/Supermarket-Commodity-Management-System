#include "sqlvip.h"
#include"mysql.h"



QVector<Vip> SqlVip::Query(int id, QString name, QString number, double minpoint, double maxpoint, int minlevel, int maxlevel, QDate minrdate, QDate maxrdate)
{

    QString sql = QString("SELECT * from vip_table WHERE");


    if(id != -1){
        sql += QString(" Id = %1 AND ").arg(id);
    }
    if(name != ""){
        sql += QString(" Name Like '%%1%' AND ").arg(name);
    }
    if(number !=""){
        sql +=QString(" PhoneNumber LIKE '%%1%' AND ").arg(number);
    }
    if(minpoint <= maxpoint){
        sql += QString(" Point between %1 and %2 AND ").arg(minpoint).arg(maxpoint);
    }
    if(minlevel <= maxlevel){
        sql += QString(" Level between %1 and %2 AND ").arg(minlevel).arg(maxlevel);
    }
    if(!minrdate.isNull() && !maxrdate.isNull()){
        sql += QString(" RegisterDate between '%1' and '%2' AND ").arg(minrdate.toString("yyyy-MM-dd")).arg(maxrdate.toString("yyyy-MM-dd"));
    }

   
    sql = sql.left(sql.length() - 5)+";";
    qDebug()<<sql;
    QSqlQuery query = MySql::getInstance().query(sql);
    QVector<Vip> result;
    while(query.next()){
        result.push_back(Vip(query.value(0).toInt(),query.value(1).toString(),
                             query.value(2).toString(),query.value(3).toDouble(),
                             query.value(4).toInt(),query.value(5).toDate()));
    }
    return result;
}

bool SqlVip::insert(QString& name, QString& phone, double point, int level, QDate date)
{
    QString sql = QString("INSERT INTO vip_table(Name,PhoneNumber,Point,Level,RegisterDate) "
                          "VALUES('%1','%2',%3,%4,'%5')").arg(name).arg(phone).arg(point).arg(level).arg(date.toString("yyyy-MM-dd"));

    qDebug()<<sql;
    return MySql::getInstance().modify(sql);
}

QVector<Vip> SqlVip::Query(QString number)
{
    QString sql = QString("SELECT * from vip_table WHERE PhoneNumber = '%1';").arg(number);
    qDebug()<<sql;
    QSqlQuery query = MySql::getInstance().query(sql);
    QVector<Vip> result;
    while(query.next()){
        result.push_back(Vip(query.value(0).toInt(),query.value(1).toString(),
                             query.value(2).toString(),query.value(3).toDouble(),
                             query.value(4).toInt(),query.value(5).toDate()));
    }
    return result;
}

bool SqlVip::modify(int id, QString num, double point, int lev)
{
    QString sql = " UPDATE vip_table SET ";
    QStringList updates;
    if(!num.isEmpty())
    {
        updates.append(QString("PhoneNumber = '%1'").arg(num));
    }
    if(point!=-1)
    {
        updates.append(QString("Point = %1").arg(point));
    }
    if(lev != -1)
    {
        updates.append(QString("Level = %1").arg(point));
    }
    if (updates.isEmpty()) {
        // 如果没有需要更新的字段，则直接返回
        qDebug()<<"商品信息不需要更新";
        return false;
    }

    sql += updates.join(", ");
    sql += QString(" WHERE Id = %1 ;").arg(id);
    qDebug()<<sql;
    return MySql::getInstance().modify(sql);
}
