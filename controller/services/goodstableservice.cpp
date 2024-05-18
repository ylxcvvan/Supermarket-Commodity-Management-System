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

bool GoodsTableService::CommitGList()
{
    //TODO
    return true;
}
