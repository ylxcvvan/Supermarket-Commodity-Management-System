#include "inventorytable.h"

InventoryTable::InventoryTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"库存单号","商品编号","名称名称","商品数量","商品进价","商品描述","商品保质期"};
}

QVariant InventoryTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
    // FIXME: Implement me!
}

int InventoryTable::rowCount(const QModelIndex &parent) const
{

        return 0;

    // FIXME: Implement me!
}

int InventoryTable::columnCount(const QModelIndex &parent) const
{

    return 0;
    // FIXME: Implement me!
}

QVariant InventoryTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool InventoryTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags InventoryTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool InventoryTable::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool InventoryTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

