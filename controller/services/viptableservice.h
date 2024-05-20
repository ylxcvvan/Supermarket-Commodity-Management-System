#ifndef VIPTABLESERVICE_H
#define VIPTABLESERVICE_H
#include"view/table/viptable.h"
class VipTableService
{
public:
    VipTableService();
    ~VipTableService();

    VipTable* getTable();
    void setTable(QVector<Vip> viptable);
    void sortByColumn(int column,Qt::SortOrder order);
private:
    VipTable* viptable;
};

#endif // VIPTABLESERVICE_H
