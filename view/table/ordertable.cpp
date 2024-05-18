#include "ordertable.h"

OrderTable::OrderTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"订单单号","订单日期","收银员id","顾客id","应付金额","实付金额","订单状态"};
}

QVariant OrderTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}


int OrderTable::rowCount(const QModelIndex &parent) const
{
    return ordList.size();
}

int OrderTable::columnCount(const QModelIndex &parent) const
{
    return titles.size();
}

QVariant OrderTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {
        return ordList[index.row()][index.column()];
    }

    return QVariant();
}

bool OrderTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags OrderTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags &= ~Qt::ItemIsEditable; // 移除编辑标志
    return flags;
}

bool OrderTable::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}
bool OrderTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

void OrderTable::setOrdList(QVector<QVector<QVariant>> &&newlist)
{
    beginResetModel(); // 开始重置模型，通知视图整体更新
    ordList=std::move(newlist);
    endResetModel();
}

