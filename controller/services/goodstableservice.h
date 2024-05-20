#ifndef GOODSTABLESERVICE_H
#define GOODSTABLESERVICE_H
#include "view/table/goodstable.h"
#include "model/commodity.h"
class GoodsTableService
{
public:
    GoodsTableService();
    ~GoodsTableService();

    GoodsTable* getGTable();
    void setGList(QVector<QVector<QVariant>>&& newglist);
private:
    GoodsTable *gtable;

public slots:
    //提交订单
    bool CommitGList();

};

#endif // GOODSTABLESERVICE_H
