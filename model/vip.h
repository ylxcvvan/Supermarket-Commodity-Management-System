#ifndef VIP_H
#define VIP_H
#include<QString>
#include<QDate>
class Vip
{
private:
    QString Name;
    QString PhoneNumber;
    int Id;
    double Point;
    int Level;
    QDate RegisterDate;

public:
    Vip(int id,QString name,QString phone,double p,int l,QDate Reg);

    const QString& getName();
    const QString& getPhoneNumber();
    const int& GetId();
    double getPoint();
    int getLevel();
    const QDate& getRegisterDate();

    void setLevel(const int& newLevel);
    void setPoint(const double& newPoint);
    void setPhoneNumber(const QString& newPhoneNumber);
};

#endif // VIP_H
