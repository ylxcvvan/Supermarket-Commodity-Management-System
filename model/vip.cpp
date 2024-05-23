#include "vip.h"

Vip::Vip(int id, QString name, QString phone, double p, int l, QDate Reg):
    Name(name),PhoneNumber(phone),Id(id),Point(p),Level(l),RegisterDate(Reg){}

const QString &Vip::getName() const
{
    return this->Name;
}

const QString &Vip::getPhoneNumber() const
{
    return this->PhoneNumber;
}

const int &Vip::getId() const
{
    return this->Id;
}

const double &Vip::getPoint() const
{
    return this->Point;
}

const int &Vip::getLevel() const
{
    return this->Level;
}

const QDate &Vip::getRegisterDate() const
{
    return this->RegisterDate;
}

void Vip::setName(const QString &name){
    Name = name;
}

void Vip::setRegisterDate(QDate date){
    RegisterDate = date;
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




