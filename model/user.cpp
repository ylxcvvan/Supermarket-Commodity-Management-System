#include "user.h"

User::User(int id, QString name, QString account, QString password, QDateTime time):
    Id(id),
    Name(name),
    Account(account),
    Password(password),
    LastLoginTime(time){}

const QString &User::getName()
{
    return this->Name;
}

const QString &User::getPassword()
{
    return this->Password;
}

const int &User::getId()
{
    return this->Id;
}

const QString &User::getAccount()
{
    return this->Account;
}

const QString &User::getDateTime()
{
    return this->getDateTime();
}
