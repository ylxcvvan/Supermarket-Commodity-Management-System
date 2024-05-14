#ifndef MYSQLOPERATE_H
#define MYSQLOPERATE_H
#include"mysql.cpp"
#include<QSqlQuery>
#include<QSqlError>
class MySqlOperate
{
public:

    MySqlOperate();

private:

    QSqlDatabase *db;

    bool update(const QString& sql);
    QSqlQuery query(const QString& sql);
};

#endif // MYSQLOPERATE_H
