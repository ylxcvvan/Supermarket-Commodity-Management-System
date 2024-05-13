#include "modeluser.h"

ModelUser::ModelUser() {}

const QString &ModelUser::getName()
{
    return this->name;
}

const QString &ModelUser::getPassword()
{
    return this->password;
}
