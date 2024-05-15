#ifndef MYSQL_H
#define MYSQL_H

#include <QtSql/QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>
#include <QtSql/QSqlDatabase>
class MySql
{
public:
    static MySql& getInstance();
    QSqlDatabase& getDatabase();


    bool modify(const QString& sql);
    QSqlQuery query(const QString& sql);
    bool insert(const QString& sql);
    bool del(const QString& sql);

private:
    QSqlDatabase db;

    MySql();
    MySql(MySql const&) = delete;
    void operator=(MySql const&)  = delete;

};

#endif // MYSQL_H
