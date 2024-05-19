#include "sqlcashier.h"



bool SqlCashier::login(QString account, QString password)
{
    QString sql = QString("SELECT * FROM cashier_table  Where Account = %1 AND Password = %2;")
                      .arg(account).arg(password);

    auto res = MySql::getInstance().query(sql);
    return res.size();
}

User SqlCashier::query(int id)
{
    QString sql = QString("SELECT * FROM cashier_table where Id = %1;").arg(id);

    auto res = MySql::getInstance().query(sql);
    return User(res.value(0).toInt(),res.value(1).toString(),res.value(2).toString(),
                res.value(3).toString(),res.value(4).toDateTime());
}
