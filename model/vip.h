#ifndef VIP_H
#define VIP_H
#include<QString>
#include<QDate>
class Vip
{
private:
    QString Name;
    QString PhoneNumber;
    QString Id;
    double Point;
    int Level;
    QDate RegisterDate;

public:
    Vip();

    const QString& getName();
    const QString& getPhoneNumber();
    const QString& GetId();
    double getPoint();
    int getLevel();
    const QDate& getRegisterDate();

    void setLevel(const int& newLevel);
    void setPoint(const double& newPoint);
    void setPhoneNumber(const QString& newPhoneNumber);
};

#endif // VIP_H
