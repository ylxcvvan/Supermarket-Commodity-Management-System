#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QAbstractTableModel>
#include"model/commodity.h"
class InventoryTable : public QAbstractTableModel
{
    Q_OBJECT
private:

    QVector<QString>titles;
    //库存单号","商品编号","商品名称","商品类别","商品描述",商品数量","商品进价","商品保质期",
    QVector<QVector<QVariant>>itable;

public:
    explicit InventoryTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    //传入新的itable参数构造新的itablei

    void setITable(QVector<QVector<QVariant>>&& newtable);

};

#endif // INVENTORYTABLE_H
