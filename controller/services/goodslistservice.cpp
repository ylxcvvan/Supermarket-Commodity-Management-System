#include "goodslistservice.h"

GoodsListService::GoodsListService():
    glist(new GoodsList)
{}

GoodsListService::~GoodsListService()
{
    delete glist;
}

GoodsList* GoodsListService::getGlist()
{
    return glist;
}

bool GoodsListService::CommitGoodlist()
{
    //TODO
    return true;
}
