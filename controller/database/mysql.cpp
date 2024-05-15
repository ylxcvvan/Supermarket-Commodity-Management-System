#include "mysql.h"
MySql &MySql::getInstance()
{
    static MySql instance;
    return instance;
}



QSqlDatabase& MySql::getDatabase()
{
    return db;
}


MySql::MySql()
    :db(QSqlDatabase::addDatabase("QMYSQL"))
{
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("scmsdb");
    db.setUserName("scms");
    db.setPassword("123456");
    if(!db.open()){
        qDebug() << "连接数据库失败";

    }else{
        qDebug() <<"连接数据库成功";
    }
}

bool MySql::modify(const QString &sql)
{
    QSqlQuery query(db);
    query.prepare(sql);
    if (!query.exec()) {
        qDebug() << "Error: Unable to execute query" << query.lastError();
        return false;
    } else {
        return true;
    }
}

QSqlQuery MySql::query(const QString &sql)
{
    QSqlQuery query(db);
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


