#include "vip.h"

Vip::Vip() {}

const QString &Vip::getName()
{
    return this->Name;
}

const QString &Vip::getPhoneNumber()
{
    return this->PhoneNumber;
}

const QString &Vip::GetId()
{
    return this->Id;
}

double Vip::getPoint()
{
    return this->Point;
}

int Vip::getLevel()
{
    return this->Level;
}

const QDate &Vip::getRegisterDate()
{
    return this->RegisterDate;
}

void Vip::setLevel(const int &newLevel)
{
    this->Level=newLevel;
}

void Vip::setPoint(const double &newPoint)
{
    this->Point=newPoint;
}

void Vip::setPhoneNumber(const QString &newPhoneNumber)
{
    this->PhoneNumber=newPhoneNumber;
}




