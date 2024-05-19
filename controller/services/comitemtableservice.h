#ifndef COMITEMTABLESERVICE_H
#define COMITEMTABLESERVICE_H
#include"view/table/comitemtable.h"
class ComItemTableService
{
public:
    ComItemTableService();
    ~ComItemTableService();
    ComItemTable* getTable(int index);
    void setComItemList(int index,QVector<CommodityItem>&&newitem);
    ComItemDelegate *getComItemDelegate();
private:
    QVector<ComItemTable*>ItemTableList;
    ComItemDelegate *comitemdelegate;
};

#endif // COMITEMTABLESERVICE_H
