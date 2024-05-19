#include "sqlvip.h"
#include"mysql.h"

Vip SqlVip::Query(int id)
{
    QString sql =QString("SELECT * FROM vip_table WHERE Id = '%1';").arg(id);

    auto res = MySql::getInstance().query(sql);

    return Vip(res.value(0).toInt(),res.value(1).toString(),res.value(2).toString(),
               res.value(3).toDouble(),res.value(4).toInt(),QDate::fromString(res.value(5).toString()));
}
