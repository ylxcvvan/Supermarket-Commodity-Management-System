#include "user.h"

User::User(int id, QString name, QString account, QString password):
    Name(id),Password(name){}

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
    return this->id;
}

const QString &User::getAccount()
{
    return this->Account;
}
