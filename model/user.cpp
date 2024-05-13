#include "user.h"

User::User(QString n, QString pwd):
    Name(n),Password(pwd){}

const QString &User::getName()
{
    return this->Name;
}

const QString &User::getPassword()
{
    return this->Password;
}
