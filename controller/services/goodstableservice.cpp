#include "goodstableservice.h"

GoodsTableService::GoodsTableService():
    gtable(new GoodsTable)
{}

GoodsTableService::~GoodsTableService()
{
    delete gtable;
}

GoodsTable* GoodsTableService::getGTable()
{
    return gtable;
}

void GoodsTableService::setGList(QVector<QVector<QVariant>> &&newglist)
{
    gtable->setGoodsList(std::forward<QVector<QVector<QVariant>>&&>(newglist));
}

bool GoodsTableService::CommitGList()
{
    //TODO
    return true;
}
