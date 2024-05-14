#ifndef MYSQL_H
#define MYSQL_H

#include <QtSql/QSqlDatabase>
#include<QDebug>
class MySql
{
public:
    static MySql& getInstance();

    QSqlDatabase& getDatabase();

private:
    QSqlDatabase db;

    MySql();
    MySql(MySql const&) = delete;
    void operator=(MySql const&)  = delete;
};

#endif // MYSQL_H
