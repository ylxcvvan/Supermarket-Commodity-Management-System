#include "sqlvip.h"
#include"mysql.h"



QVector<Vip> SqlVip::Query(int id, QString name, QString number, double minpoint, double maxpoint, int minlevel, int maxlevel, QDate minrdate, QDate maxrdate)
{
    QString sql = QString("SELECT * from vip_table WHERE");

    if(id != -1){
        sql += QString("Id = %1 AND ").arg(id);
    }
    if(name != ""){
        sql += QString("Name = %1 AND").arg(name);
    }
    if(number !=""){
        sql +=QString("PhoneNumber LIKE '%1' AND ").arg(number);
    }
    if(minpoint < maxpoint){
        sql += QString("Point between %1 and %2 AND").arg(minpoint).arg(maxpoint);
    }
    if(minlevel < maxlevel){
        sql += QString("Level between %1 and %2 AND").arg(minlevel).arg(maxlevel);
    }
    if(!minrdate.isNull() && !maxrdate.isNull()){
        sql += QString("RegisterDate between '%1' and '%2' and ").arg(minrdate.toString("yyyy-MM-dd")).arg(maxrdate.toString("yyyy-MM-dd"));
    }

    sql = sql.left(sql.length() - 5)+";";

    QSqlQuery query = MySql::getInstance().query(sql);
    QVector<Vip> result;
    while(query.next()){
        result.push_back(Vip(query.value(0).toInt(),query.value(1).toString(),
                             query.value(2).toString(),query.value(3).toDouble(),
                             query.value(4).toInt(),query.value(5).toDate()));
    }
    return result;
}
