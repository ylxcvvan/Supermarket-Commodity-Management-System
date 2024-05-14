#include "mysqloperate.h"
#include"mysql.h"
#include"mysql.cpp"
MySqlOperate::MySqlOperate()
    :db(&MySql::getInstance().getDatabase()){}


bool MySqlOperate::update(const QString &sql)
{
    QSqlQuery query(*db);
    query.prepare(sql);
    if (!query.exec()) {
        qDebug() << "Error: Unable to execute query" << query.lastError();
        return false;
    } else {
        return true;
    }
}

QSqlQuery MySqlOperate::query(const QString &sql)
{
    QSqlQuery query(*db);
    query.prepare(sql);
    bool success = false;
    int retryCount = 3;
    int currentAttempt = 0;
    while (!success && currentAttempt < retryCount) {
        if (query.exec()) {
            success = true;
            return query;
        } else {
            qDebug() << "Error: Unable to execute query. Retry attempt" << currentAttempt + 1;
            qDebug() << "Error details:" << query.lastError();
            ++currentAttempt;
            return QSqlQuery();
        }
    }
    if (!success) {
        qDebug() << "Failed to execute query after" << retryCount << "attempts";
        return QSqlQuery();
    }
}
