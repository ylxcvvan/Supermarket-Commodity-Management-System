#ifndef SQLINVENTORY_H
#define SQLINVENTORY_H
#include"mysql.h"
#include <QSqlQuery>
#include <QVariant>
namespace SqlInventory
{

    //库存单号","商品编号","商品名称","商品类别","商品描述",商品数量","商品进价","商品保质期",
    QVector<QVector<QVariant>> QueryInventory(int id=-1,int cid=-1,double camount=-1);

    //TODO
    bool Del();
    bool Modify();
    bool Insert();
};

#endif // SQLINVENTORY_H
