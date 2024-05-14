#ifndef INVENTORYTABLESERVICE_H
#define INVENTORYTABLESERVICE_H
#include "view/table/inventorytable.h"
class InventoryTableService
{
public:
    InventoryTableService();
    ~InventoryTableService();
    InventoryTable* getITable();

private:
    InventoryTable *itable;
};

#endif // INVENTORYTABLESERVICE_H
