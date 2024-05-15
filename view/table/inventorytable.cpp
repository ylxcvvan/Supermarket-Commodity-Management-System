#include "inventorytable.h"
#include "qdebug.h"

InventoryTable::InventoryTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"库存单号","商品编号","商品名称","商品类别","商品描述","商品数量","商品进价","商品保质期"};
}

QVariant InventoryTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}

int InventoryTable::rowCount(const QModelIndex &parent) const
{
    return itable.size();
}

int InventoryTable::columnCount(const QModelIndex &parent) const
{
    return titles.size();
}

QVariant InventoryTable::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {
        return itable[index.row()][index.column()];
    }

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
    //TODO
    endInsertRows();
    return true;
}

bool InventoryTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    //TODO
    endRemoveRows();
    return true;
}

void InventoryTable::setITable(QVector<QVector<QVariant>> &&newtable)
{
    itable=std::move(newtable);

}

