#include "viptableservice.h"



VipTableService::VipTableService()
    :viptable(new VipTable())
{

}

VipTableService::~VipTableService()
{
    delete viptable;
}

VipTable *VipTableService::getTable()
{
    return viptable;
}

void VipTableService::setTable(QVector<Vip> viptable)
{
    this->viptable->setVipList(std::forward<QVector<Vip>&&>(viptable));
}

