#ifndef COMMODITY_H
#define COMMODITY_H
#include<QDate>
#include<QString>
class Commodity
{
private:
    QString Name;
    double Price;
    double CostPrice;
    QString Id;
    QDate sellByTime;
    QString Details;

public:
    Commodity();

    //获取商品属性
    const QString& getName();
    const double& getPrice();
    const double& getcostPrice();
    const QString& getId();
    const QDate& getSellByTime();
    const QString& getDetails();

    int getQuantity();
    //修改商品属性
    bool setName(const QString& newName);
    bool setPrice(const double& newPrice);
    bool setDetails(const QString& newDetails);


};
#endif // COMMODITY_H
