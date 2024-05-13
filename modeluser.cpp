#include "modeluser.h"

ModelUser::ModelUser(QString n, QString pwd):
    Name(n),Password(pwd){}

const QString &ModelUser::getName()
{
    return this->Name;
}

const QString &ModelUser::getPassword()
{
    return this->Password;
}
