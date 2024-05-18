#include "sqlorder.h"
#include"./model/orderitem.h"
#include"mysql.h"
#include"sqlorderitem.h"


QVector<Order> SqlOrder::Query(int orderid, QDateTime orderdatebegin,QDateTime orderdateend, int orderstate, double mintotal, double maxtotal,
                               double minpaid, double maxpaid, int consumerid, int cashierid)
{
    QString sql = "SELECT * FROM order_table WHERE";
    if(orderid != -1){
        sql += QString(" OrderId = %1 AND ").arg(orderid);
    }
    if(orderdatebegin<orderdateend){
        sql += QString(" OrderDate BETWEEN '%1' AND '%2' AND ").arg(orderdatebegin.toString("yyyy-MM-dd HH:mm:ss")).arg(orderdateend.toString("yyyy-MM-dd HH:mm:ss"));
    }
    if(orderstate != -1){
        sql += QString(" OrderState = %1 AND ").arg(orderstate);
    }
    if(mintotal < maxtotal){
        sql +=QString(" TotalPrice BETWEEN %1 AND %2 AND ").arg(mintotal).arg(maxtotal);
    }
    if(minpaid < maxpaid){
        sql +=QString(" PaidPrice BETWEEN %1 AND %2 AND ").arg(minpaid).arg(maxpaid);
    }
    if(consumerid != -1){
        sql +=QString(" ConsumerId = %1 AND ").arg(consumerid);
    }
    if(cashierid != -1){
        sql +=QString(" CashierId = %1 AND ").arg(cashierid);
    }

    sql = sql.left(sql.length() - 5)+";";

    qDebug()<<sql;
    QSqlQuery query = MySql::getInstance().query(sql);
    QVector<Order>result;
    while(query.next()){
        QVector<OrderItem> itemlist = SqlOrderItem::Query(query.value(0).toInt());
        auto time = QDateTime::fromString(query.value(1).toString(), "yyyy-MM-ddTHH:mm:ss.000");

        qDebug()<<"订单时间："<<query.value(1).toString();
        auto it=Order::stage::Completed;
        switch(query.value(2).toInt())
        {
        case 0:{
            it = Order::stage::Pending;
            break;
        }
        case 1:{
            it= Order::stage::cancelled;}
        break;
        }


      //Order::Order(int oid,Glist gl,double tp,double pp,int uid, int cid,state st,QDateTime ti):
        Order order(query.value(0).toInt(),
                    itemlist,
                    query.value(3).toDouble(),
                    query.value(4).toDouble(),
                    query.value(5).toInt(),
                    query.value(6).toInt(),
                    it,
                    time);

        result.push_back(order);
    }
    return result;
}

bool SqlOrder::insert(Order order)
{
    //Pending=0,cancelled=1,Completed=2
    int state = 2;
    Order::stage s = order.getOrderStage();
    switch(s){
    case Order::stage::Pending :{
            state = 0;
            break;
        }
    case Order::stage::cancelled : {
            state = 1;
            break;
        }
    default:
            break;
    }

    QString sql = QString("insert into order_table (OrderId,OrderDate,OrderState,TotalPrice,PaidPrice,ConsumerId,CashierId) "
                   "values(%1,'%2',%3,%4,%5,%6,%7)")
                        .arg(order.getOrderId())
                        .arg(order.getOrderTime().toString("yyyy-MM-dd HH:mm:ss"))
                        .arg(state)
                        .arg(order.getTotalPrice())
                        .arg(order.getPaidPrice())
                        .arg(order.getUserId())
                        .arg(order.getCashierId());
    qDebug()<<sql;
    bool insertorder = MySql::getInstance().modify(sql);
    bool insertorderitem ;
    auto googlist = order.getGoodsList();
    for(auto i : googlist){
        QString Sql = QString("insert into orderitem_table(OrderId,CommodityId,CommodityAmount,TotalPrice) "
                              "values(%1,%2,%3<%4)")
                          .arg(order.getOrderId())
                          .arg(i.getCommodityId())
                        .arg(i.getCommodityAmount())
                        .arg(i.getTotalPrice());
        qDebug()<<Sql;
        insertorderitem = MySql::getInstance().modify(Sql);
    }


    return insertorder && insertorderitem;

}
