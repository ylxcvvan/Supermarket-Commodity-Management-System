#include "sqlcashier.h"



bool SqlCashier::login(QString account, QString password)
{
    QString sql = QString("SELECT * FROM cashier_table  Where Account = '%1' AND Password = '%2';")
                      .arg(account).arg(password);

    auto res = MySql::getInstance().query(sql);
    return res.size();
}
User SqlCashier::query(int id)
{
    QString sql = QString("SELECT * FROM cashier_table where Id = %1;").arg(id);

    qDebug() << sql;
    QSqlQuery res = MySql::getInstance().query(sql);

    // 检查是否有结果
    //修复了收银员姓名显示异常的bug
    res.next();
      // 或者返回一个表示未找到的 User 对象


    // 现在 res 指向第一条记录，可以安全地访问数据
    return User(res.value(0).toInt(), res.value(1).toString(), res.value(2).toString(),
                res.value(3).toString(), res.value(4).toDateTime());
}

int SqlCashier::queryAccount(QString account)
{
    QString sql = QString("SELECT * FROM cashier_table  Where Account = '%1';")
                      .arg(account);
    qDebug()<<sql;
    auto res = MySql::getInstance().query(sql);
    res.next();
    qDebug()<<res.value(0);
    return res.value(0).toInt();
}
