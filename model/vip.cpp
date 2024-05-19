#include "vip.h"

Vip::Vip(int id, QString name, QString phone, double p, int l, QDate Reg):
    Name(name),PhoneNumber(phone),Id(id),Point(p),Level(l),RegisterDate(Reg){}

const QString &Vip::getName()
{
    return this->Name;
}

const QString &Vip::getPhoneNumber()
{
    return this->PhoneNumber;
}

const int &Vip::getId()
{
    return this->Id;
}

double& Vip::getPoint()
{
    return this->Point;
}

int &Vip::getLevel()
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




