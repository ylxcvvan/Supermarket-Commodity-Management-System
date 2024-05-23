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

bool SqlCashier::updatePassword(QString account, QString newPassword)
{
    QString sql = QString("UPDATE cashier_table SET Password = '%1' WHERE Account = '%2';")
                      .arg(newPassword).arg(account);

    qDebug() << sql;
    QSqlQuery query = MySql::getInstance().query(sql);

    if (query.exec()) {
        qDebug() << "Password updated successfully.";
        return true;
    } else {
        qDebug() << "Failed to update password.";
        return false;
    }
}

QDateTime SqlCashier::queryLastLogintime(QString account) {
    QString sql = QString("SELECT LastLoginDate FROM cashier_table WHERE Account = '%1';")
                      .arg(account);

    qDebug() << sql;
    QSqlQuery query = MySql::getInstance().query(sql);

    if (query.exec() && query.next()) {
        QDateTime lastLoginDate = query.value(0).toDateTime();
        return lastLoginDate;
    } else {
        qDebug() << "Failed to query last login time or no result found." << query.lastError();
        return QDateTime();
    }
}

bool SqlCashier::updateLastLoginTime(QString account) {
    QDateTime currentTime = QDateTime::currentDateTime();
    QString sql = QString("UPDATE cashier_table SET LastLoginDate = '%1' WHERE Account = '%2';")
                      .arg(currentTime.toString("yyyy-MM-dd HH:mm:ss")).arg(account);

    qDebug() << sql;
    QSqlQuery query = MySql::getInstance().query(sql);

    if (query.exec()) {
        qDebug() << "上次登录时间更新成功";
        return true;
    } else {
        qDebug() << "Failed to update last login time." << query.lastError();
        return false;
    }
}
