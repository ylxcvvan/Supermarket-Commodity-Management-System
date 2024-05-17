#include "goodslistservice.h"

GoodsListService::GoodsListService():
    glist(new GoodsTable)
{}

GoodsListService::~GoodsListService()
{
    delete glist;
}

GoodsTable* GoodsListService::getGlist()
{
    return glist;
}

bool GoodsListService::CommitGoodlist()
{
    //TODO
    return true;
}
