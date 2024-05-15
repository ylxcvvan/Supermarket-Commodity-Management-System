#include "inventorytableservice.h"

InventoryTableService::InventoryTableService()
    :itable(new InventoryTable)
{}

InventoryTableService::~InventoryTableService()
{
    delete itable;
}

InventoryTable *InventoryTableService::getITable()
{
    return itable;
}

void InventoryTableService::setITableArray(QVector<QVector<QVariant>>&& newitable)
{
    this->itable->setITable(std::forward<QVector<QVector<QVariant>>&&>(newitable));
}

void InventoryTableService::sortByColumn(int column, Qt::SortOrder order)
{
    //TODO
}
