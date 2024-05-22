#include "allcomitemtableservice.h"

AllComItemTableService::AllComItemTableService()
    :allcomitemtable(new AllComItemTable)
{}

AllComItemTableService::~AllComItemTableService()
{
    delete allcomitemtable;
}

void AllComItemTableService::setAllComItemTable(QVector<CommodityItem> &&newcilist)
{
    allcomitemtable->setCItemList(std::move(newcilist));
}

AllComItemTable *AllComItemTableService::getTable()
{
    return allcomitemtable;
}
