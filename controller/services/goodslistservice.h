#ifndef GOODSLISTSERVICE_H
#define GOODSLISTSERVICE_H
#include "view/table/goodslist.h"
#include "model/commodity.h"
class GoodsListService
{
public:
    GoodsListService();
    ~GoodsListService();
    GoodsList* getGlist();

private:
    GoodsList *glist;

public slots:
    bool CommitGoodlist();

};

#endif // GOODSLISTSERVICE_H
