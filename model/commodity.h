#ifndef COMMODITY_H
#define COMMODITY_H
#include<QDate>
#include<QString>
class Commodity
{
private:
    QString Id;
    QString Name;
    double Price;
    double CostPrice;
    QDate sellByTime;
    QString Details;

public:
    Commodity(QString na="未命名",double p=0,double cp=0,QDate sbt=QDate(),QString Details="该商品没有描述");
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
