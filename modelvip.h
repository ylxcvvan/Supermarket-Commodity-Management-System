#ifndef MODELVIP_H
#define MODELVIP_H
#include<QString>
#include<QDate>
class ModelVip
{
private:
    QString Name;
    QString PhoneNumber;
    QString Number;
    double Point;
    int Level;
    QDate RegisterDate;

public:
    ModelVip();

    const QString& getName();
    const QString& getPhoneNumber();
    const QString& GetNumber();
    double getPoint();
    int getLevel();
    const QDate& getRegisterDate();

    void setLevel(const int& newLevel);
    void setPoint(const double& newPoint);
    void setPhoneNumber(const QString& newPhoneNumber);
};

#endif // MODELVIP_H
