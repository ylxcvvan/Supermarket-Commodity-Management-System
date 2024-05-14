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
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("scmsdb");
    db.setUserName("scms");
    db.setPassword("123456");
    if(!db.open()){
        qDebug() << "连接数据库失败";
    }else{
        qDebug() <<"连接数据库成";
    }
}



