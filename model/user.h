#ifndef USER_H
#define USER_H
#include "qdatetime.h"
#include<QString>
class User
{
private:
    int Id;
    QString Name;
    QString Account;
    QString Password;
    QDateTime LastLoginTime;


public:
    User(int id,QString name,QString account,QString password,QDateTime time);

    const QString& getName();
    const QString& getPassword();
    const int& getId();
    const QString& getAccount();
    const QString& getDateTime();
};

#endif // USER_H
