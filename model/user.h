#ifndef USER_H
#define USER_H
#include<QString>
class User
{
private:
    QString Name;
    QString Password;

public:
    User(QString n,QString pwd="123456");

    const QString& getName();
    const QString& getPassword();
};

#endif // USER_H
