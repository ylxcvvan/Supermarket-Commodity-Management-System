#ifndef MYSQLOPERATE_H
#define MYSQLOPERATE_H
#include<QSqlQuery>
#include<QSqlError>
#include <QtSql/QSqlDatabase>
#include"mysql.h"
class MySqlOperate
{
public:

    MySqlOperate();
    bool modify(const QString& sql);
    QSqlQuery query(const QString& sql);
    bool insert(const QString& sql);
    bool del(const QString& sql);


private:

    QSqlDatabase *db;


};

#endif // MYSQLOPERATE_H
