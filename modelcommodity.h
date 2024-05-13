#ifndef MODELCOMMODITY_H
#define MODELCOMMODITY_H
#include<QDate>
#include<QString>
class ModelCommodity
{
private:
    QString name;
    double price;
    double costPrice;
    QString Number;
    QDate sellByTime;
    QString Details;

public:
    ModelCommodity();

    //获取商品属性
    const QString& getName();
    const double& getPrice();
    const double& getcostPrice();
    const QString& getNumber();
    const QDate& getSellByTime();
    const QString& getDetails();

    //修改商品属性
    bool setName(const QString& newName);
    bool setPrice(const double& newPrice);
    bool setDetails(const QString& newDetails);

};

#endif // MODELCOMMODITY_H
