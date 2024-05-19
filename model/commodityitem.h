#ifndef COMMODITYITEM_H
#define COMMODITYITEM_H
#include<QString>
#include <QMetaType>

/*
    食品类：包括各种食品和饮料，如谷物、肉类、水果、蔬菜、饮料等。
    日用品类：包括洗涤用品、洗浴用品、家庭清洁用品、纸制品等。
    服装类：包括各种服装、鞋帽、配饰等。
    家电类：包括电视、冰箱、洗衣机、空调等家用电器。
    数码产品类：包括手机、电脑、相机、平板电脑等。
    家具类：包括沙发、床、桌椅、柜子等各种家具。
    办公用品类：包括笔、纸张、文件夹、打印机等各种办公用品。
    运动健身类：包括运动服装、运动器材、健身器材等。
    图书音像类：包括图书、音乐CD、电影DVD等。
    礼品类：包括各种礼品、鲜花、卡片等。
*/

class CommodityItem
{

private:
    int ItemId;
    QString Name;
    QString Details;
    QString Category;

public:
    CommodityItem();
    CommodityItem(int iid,QString na,QString de="该商品没有描述",QString ca="未分类");
    int getItemId() const;
    QString getName() const;
    QString getDetails() const;
    QString getCategory() const;

    void setName(const QString& newname);
    void setDetails(const QString& newdetails);
    void setCategory(const QString& newcategory);
};
Q_DECLARE_METATYPE(CommodityItem)

#endif // COMMODITYITEM_H
