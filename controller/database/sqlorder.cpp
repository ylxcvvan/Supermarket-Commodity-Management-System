#include "sqlorder.h"



QVector<Order> SqlOrder::Query(int orderid, QDate orderdate, int orderstate, double mintotal, double maxtotal, int consumerid)
{
    QString sql = "SELECT * FROM order_table WHERE";
    if(orderid != -1){
        sql += QString(" OrderId = %1 AND ").arg(orderid);
    }
    if(!orderdate.isNull()){
        sql += QString(" OrderDate <'%1' AND ").arg(orderdate.toString("yyyy-MM-dd HH:mm:ss"));
    }
    if(orderstate != -1){
        sql += QString(" OrderState = %1 AND ").arg(orderstate);
    }
    if(mintotal < maxtotal){
        sql +=QString(" TotalPrice BETWEEN %1 AND %2 AND ").arg(mintotal).arg(maxtotal);
    }
    if(consumerid != -1){
        sql +=QString(" ConsumerId = %1 ").arg(consumerid);
    }
    sql = sql.left(sql.length() - 5)+";";

   QSqlQuery query = MySql::getInstance().query(sql);
    QVector<Order>result;
    while(query.next()){
        QVector<OrderItem> itemlist = SqlOrderItem::Query(query.value(0).toInt());
        auto time = QDateTime::fromString(query.value(1).toString());
        auto it=Order::state::Completed;
        switch(query.value(2).toInt())
        {
        case 0:{
            it = Order::state::Pending;
            break;
        }
        case 1:{
            it= Order::state::cancelled;}
        break;
        }


        //Order(int oid,Glist gl,double tp,int uid,state st=state::Pending,QDateTime ti=QDateTime::currentDateTime());
        Order order(query.value(0).toInt(),
                    itemlist,
                    query.value(3).toDouble(),
                    query.value(4).toInt(),
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
    Order::state s = order.getOrderStage();
    switch(s){
        case Order::state::Pending :{
            state = 0;
            break;
        }
        case Order::state::cancelled : {
            state = 1;
            break;
        }
    }

    QString sql = QString("insert into order_table (OrderId,OrderDate,OrderState,TotalPrice,ConsumerId) "
                   "values(%1,'%2',%3,%4,%5)")
                        .arg(order.getOrderId())
                        .arg(order.getOrderTime().toString("yyyy-MM-dd HH:mm:ss"))
                      .arg(state)
                      .arg(order.getTotalPrice())
                      .arg(order.getTotalPrice())
                      .arg(order.getUserId());
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
