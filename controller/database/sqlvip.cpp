#include "sqlvip.h"
#include"mysql.h"

Vip SqlVip::Query(QString number)
{
    QString sql =QString("SELECT * FROM vip_table WHERE PhoneNumber = '%1'").arg(number);

    auto res = MySql::getInstance().query(sql);

    return Vip(res.value(0).toInt(),res.value(1).toString(),res.value(2).toString(),
               res.value(3).toDouble(),res.value(4).toInt(),QDate::fromString(res.value(5).toString()));
}
