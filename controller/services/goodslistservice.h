#ifndef GOODSLISTSERVICE_H
#define GOODSLISTSERVICE_H
#include "view/table/goodstable.h"
#include "model/commodity.h"
class GoodsListService
{
public:
    GoodsListService();
    ~GoodsListService();
    GoodsTable* getGlist();

private:
    GoodsTable *glist;

public slots:
    //提交订单
    bool CommitGoodlist();

};

#endif // GOODSLISTSERVICE_H
