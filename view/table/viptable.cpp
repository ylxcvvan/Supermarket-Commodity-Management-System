#include "viptable.h"

VipTable::VipTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles = {"会员ID","会员名","电话","积分","等级","注册时间"};
}

QVariant VipTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}

int VipTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return std::min(pageSize, Vips.size() - currentPage * pageSize);
    // FIXME: Implement me!
}

int VipTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return titles.size();
    // FIXME: Implement me!
}

QVariant VipTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row() + currentPage * pageSize;
    if(role==Qt::DisplayRole && row < Vips.size() && index.column() < titles.size())
    {
        int column=index.column();
        auto vip=Vips[row];
        if(column==0)
            return vip.getId();
        else if(column==1)
            return vip.getName();
        else if(column==2)
            return vip.getPhoneNumber();
        else if(column==3)
            return vip.getPoint();
        else if(column==4)
            return vip.getLevel();
        else if(column==5)
            return vip.getRegisterDate();
    }
    // FIXME: Implement me!
    return QVariant();
}



bool VipTable::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool VipTable::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}

bool VipTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags VipTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags &= ~Qt::ItemIsEditable; // 移除编辑标志
    return flags;
}

bool VipTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

bool VipTable::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return true;
}

void VipTable::setPageSize(int size)
{
    pageSize = size;
    emit layoutChanged();
}

void VipTable::setCurrentPage(int page)
{
    if (page >= 0 && page < pageCount()) {
        currentPage = page;
        emit layoutChanged();
    }
}

int VipTable::pageCount() const
{
    return (Vips.size() + pageSize - 1) / pageSize;
}

int VipTable::currentPageNumber() const
{
    return currentPage;
}

void VipTable::setVipList(QVector<Vip> &&newlist)
{
    beginResetModel(); // 开始重置模型，通知视图整体更新
    Vips=std::move(newlist);
    endResetModel();
}
