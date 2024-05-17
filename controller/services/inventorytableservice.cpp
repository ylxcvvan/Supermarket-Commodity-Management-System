#include "inventorytableservice.h"

InventoryTableService::InventoryTableService()
    :itable(new InventoryTable),combodelegate(new ComboBoxDelegate)
{

}

InventoryTableService::~InventoryTableService()
{
    delete itable;
    delete combodelegate;
}

InventoryTable *InventoryTableService::getITable()
{
    return itable;
}

ComboBoxDelegate *InventoryTableService::getComboBoxDelegate()
{
    return combodelegate;
}

void InventoryTableService::setITableArray(QVector<QVector<QVariant>>&& newitable)
{
    this->itable->setInveList(std::forward<QVector<QVector<QVariant>>&&>(newitable));
}

void InventoryTableService::sortByColumn(int column, Qt::SortOrder order)
{
    //TODO
}
