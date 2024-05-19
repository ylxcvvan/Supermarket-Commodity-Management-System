#ifndef ORDERTABLESERVICE_H
#define ORDERTABLESERVICE_H
#include"view/table/ordertable.h"
class OrderTableService
{
public:
    OrderTableService();
    ~OrderTableService();
    OrderTable* getOTable();
    void setOList(QVector<Order> &&newotable);

private:
    OrderTable *otable;
};

#endif // ORDERTABLESERVICE_H
