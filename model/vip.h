#ifndef VIP_H
#define VIP_H
#include<QString>
#include<QDate>
class Vip
{
private:
    int Id;
    QString Name;
    QString PhoneNumber;
    double Point;
    int Level;
    QDate RegisterDate;

public:
    Vip(int id,QString name,QString phone,double p,int l,QDate Reg);

    const QString& getName() const;
    const QString& getPhoneNumber() const;
    const int& getId() const;
    const double& getPoint()const ;
    const int& getLevel() const;
    const QDate& getRegisterDate()const;

    void setLevel(const int& newLevel);
    void setPoint(const double& newPoint);
    void setPhoneNumber(const QString& newPhoneNumber);
};

#endif // VIP_H
