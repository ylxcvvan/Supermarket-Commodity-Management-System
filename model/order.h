#ifndef ORDER_H
#define ORDER_H
#include<QString>
#include<QDateTime>
#include<QVector>
#include<QVariant>
#include"orderitem.h"
class Order
{
    using Glist=QVector<OrderItem>;
public:
    enum class stage {Pending=0,cancelled=1,Completed=2};
private:

    int OrderId;
    //商品，商品数量，总价格计算可得
    Glist GoodsList;
    stage OrderStage;
    double TotalPrice;
    double PaidPrice;
    int UserId;
    int CashierId;
    QDateTime OrderTime;

public:

    Order(int oid,Glist gl,double tp,double pp,int uid, int cid,stage st=stage::Pending,
          QDateTime ti=QDateTime::currentDateTime());

    const int& getOrderId() const;
    const Glist& getGoodsList() const;
    stage getOrderStage() const;
    const double& getTotalPrice() const;
    const double& getPaidPrice() const;
    const int& getUserId() const;
    const int& getCashierId() const;
    const QDateTime& getOrderTime() const;

    QVariant getByColomn(int colomn);
    void setOrderStage(Order::stage newOrderStage);
};

#endif // ORDER_H
