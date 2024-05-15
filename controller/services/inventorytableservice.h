#ifndef INVENTORYTABLESERVICE_H
#define INVENTORYTABLESERVICE_H
#include "view/table/inventorytable.h"
#include "controller/database/sqlinventory.h"
class InventoryTableService
{
public:
    InventoryTableService();
    ~InventoryTableService();
    InventoryTable* getITable();
    void setITableArray(QVector<QVector<QVariant>>&& newitable);
    void sortByColumn(int column,Qt::SortOrder order);

private:
    InventoryTable *itable;
};

#endif // INVENTORYTABLESERVICE_H
