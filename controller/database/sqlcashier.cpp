#include "sqlcashier.h"



bool SqlCashier::login(QString account, QString password)
{
    QString sql = QString("SELECT * FROM cashier_table  Where Account = %1 AND Password = %2")
                      .arg(account).arg(password);

    auto res = MySql::getInstance().query(sql);
    return res.size();
}
