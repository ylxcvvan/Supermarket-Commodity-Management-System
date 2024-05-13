#ifndef MODELORDER_H
#define MODELORDER_H
#include<QString>
#include<QDateTime>
#include"modelcommodity.h"
class ModelOrder
{
private:
    enum state{Pending=0,cancelled=1,Completed=2};
    QString Number;
    QVector<ModelCommodity>GoodsList;
    state OrderStage;
    double TotalPrice;
    QString PhoneNumber;
    QDateTime OrderTime;

public:
    ModelOrder();

    const QString& getNumber();
    const QVector<ModelOrder>& getGoodsList();
    state getOrderStage();
    double getTotalPrice();
    const QString& getPhoneNumber();
    const QDateTime& getOrderTime();

    void setOrderStage(ModelOrder::state newOrderStage);
};

#endif // MODELORDER_H
