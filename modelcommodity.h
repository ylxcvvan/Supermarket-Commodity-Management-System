#ifndef MODELCOMMODITY_H
#define MODELCOMMODITY_H
#include<QDate>
#include<QString>
class ModelCommodity
{
private:
    QString Name;
    double Price;
    double CostPrice;
    QString Number;
    QDate sellByTime;
    QString Details;

    //总商品数量大小，非订单类用不到。
    int Quantity=1;
public:
    ModelCommodity();

    //获取商品属性
    const QString& getName();
    const double& getPrice();
    const double& getcostPrice();
    const QString& getNumber();
    const QDate& getSellByTime();
    const QString& getDetails();

    int getQuantity();
    //修改商品属性
    bool setName(const QString& newName);
    bool setPrice(const double& newPrice);
    bool setDetails(const QString& newDetails);

    void setQuantity(const int& newQuantity);

};

#endif // MODELCOMMODITY_H
