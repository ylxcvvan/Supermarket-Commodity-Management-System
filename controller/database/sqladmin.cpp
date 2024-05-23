#include "sqladmin.h"
#include "qdatetime.h"


bool SqlAdmin::login(QString account, QString password)
{
    QString sql = QString("SELECT * FROM admin_table Where Account = '%1' AND Password = '%2';")
        .arg(account).arg(password);

    auto res = MySql::getInstance().query(sql);
    return res.size();
}

bool SqlAdmin::updatePassword(QString account, QString newPassword) {
    QString sql = QString("UPDATE admin_table SET Password = '%1' WHERE Account = '%2';")
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

QDateTime SqlAdmin::queryLastLogintime(QString account) {
    QString sql = QString("SELECT LastLoginDate FROM admin_table WHERE Account = '%1';")
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

bool SqlAdmin::updateLastLoginTime(QString account) {
    QDateTime currentTime = QDateTime::currentDateTime();
    QString sql = QString("UPDATE admin_table SET LastLoginDate = '%1' WHERE Account = '%2';")
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
