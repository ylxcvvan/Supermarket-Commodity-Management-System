#ifndef ALLCOMITEMTABLESERVICE_H
#define ALLCOMITEMTABLESERVICE_H
#include"view/table/allcomitemtable.h"
class AllComItemTableService
{
public:
    AllComItemTableService();
    ~AllComItemTableService();
    void setAllComItemTable(QVector<CommodityItem>&&newcilist);
    AllComItemTable* getTable();
private:
    AllComItemTable *allcomitemtable;
};

#endif // ALLCOMITEMTABLESERVICE_H
