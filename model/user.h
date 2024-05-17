#ifndef USER_H
#define USER_H
#include<QString>
class User
{
private:
    int id;
    QString Name;
    QString Account;
    QString Password;


public:
    User(int id,QString name,QString account,QString password);

    const QString& getName();
    const QString& getPassword();
    const int& getId();
    const QString& getAccount();
};

#endif // USER_H
