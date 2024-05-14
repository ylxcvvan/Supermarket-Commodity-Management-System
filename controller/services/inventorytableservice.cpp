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
