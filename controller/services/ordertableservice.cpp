#include "ordertableservice.h"

OrderTableService::OrderTableService()
    :otable(new OrderTable)
{

}

OrderTableService::~OrderTableService()
{
    delete otable;
}

OrderTable *OrderTableService::getOTable()
{
    return otable;
}

void OrderTableService::setOList(QVector<Order > &&newotable)
{
    this->otable->setOrdList(std::forward<QVector<Order>&&>(newotable));
}
