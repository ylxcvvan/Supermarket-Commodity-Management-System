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

void InventoryTableService::setIList(QVector<QVector<QVariant>>&& newilist)
{
    this->itable->setInveList(std::forward<QVector<QVector<QVariant>>&&>(newilist));
}

void InventoryTableService::sortByColumn(int column, Qt::SortOrder order)
{
    this->itable->sort(column,order);
}
