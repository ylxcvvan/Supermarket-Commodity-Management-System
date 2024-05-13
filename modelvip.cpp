#include "modelvip.h"

ModelVip::ModelVip() {}

const QString &ModelVip::getName()
{
    return this->Name;
}

const QString &ModelVip::getPhoneNumber()
{
    return this->PhoneNumber;
}

const QString &ModelVip::GetId()
{
    return this->Id;
}

double ModelVip::getPoint()
{
    return this->Point;
}

int ModelVip::getLevel()
{
    return this->Level;
}

const QDate &ModelVip::getRegisterDate()
{
    return this->RegisterDate;
}

void ModelVip::setLevel(const int &newLevel)
{
    this->Level=newLevel;
}

void ModelVip::setPoint(const double &newPoint)
{
    this->Point=newPoint;
}

void ModelVip::setPhoneNumber(const QString &newPhoneNumber)
{
    this->PhoneNumber=newPhoneNumber;
}




