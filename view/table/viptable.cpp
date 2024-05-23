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

    return std::min(pageSize, vipList.size() - currentPage * pageSize);
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
    if(role==Qt::DisplayRole && row < vipList.size() && index.column() < titles.size())
    {
        int column=index.column();
        auto vip=vipList[row];
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
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    int row = index.row() + currentPage * pageSize;
    if(row >= vipList.size() || index.column() >= titles.size())
        return false;

    Vip &vip = vipList[row];
    bool dataChanged = false;

    switch (index.column()) {
    case 1:
        if (vip.getName() != value.toString()) {
            vip.setName(value.toString());
            dataChanged = true;
        }
        break;
    case 2:
        if (vip.getPhoneNumber() != value.toString()) {
            vip.setPhoneNumber(value.toString());
            dataChanged = true;
        }
        break;
    case 3:
        if (vip.getPoint() != value.toInt()) {
            vip.setPoint(value.toInt());
            dataChanged = true;
        }
        break;
    case 4:
        if (vip.getLevel() != value.toInt()) {
            vip.setLevel(value.toInt());
            dataChanged = true;
        }
        break;
    case 5:
        if (vip.getRegisterDate() != value.toDate()) {
            vip.setRegisterDate(value.toDate());
            dataChanged = true;
        }
        break;
    default:
        return false;
    }
    if (dataChanged) {
        return true;
    }
    return false;
}

Qt::ItemFlags VipTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
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

void VipTable::sort(int column, Qt::SortOrder order)
{
    std::sort(vipList.begin(), vipList.end(), [column, order](const Vip &a, const Vip &b) {
        if (order == Qt::AscendingOrder)
        {
            if(column==0)
                return a.getId()<b.getId();
            else if(column==1)
                return a.getName()<b.getName();
            else if(column==2)
                return a.getPhoneNumber()<b.getPhoneNumber();
            else if(column==3)
                return a.getPoint()<b.getPoint();
            else if(column==4)
                return a.getLevel()<b.getLevel();
            else if(column==5)
                return a.getRegisterDate()<b.getRegisterDate();

        }
        else
        {
            if(column==0)
                return a.getId()>b.getId();
            else if(column==1)
                return a.getName()>b.getName();
            else if(column==2)
                return a.getPhoneNumber()>b.getPhoneNumber();
            else if(column==3)
                return a.getPoint()>b.getPoint();
            else if(column==4)
                return a.getLevel()>b.getLevel();
            else if(column==5)
                return a.getRegisterDate()>b.getRegisterDate();
        }
        return true;
    });
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
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
    return (vipList.size() + pageSize - 1) / pageSize;
}

int VipTable::currentPageNumber() const
{
    return currentPage;
}

void VipTable::setVipList(QVector<Vip> &&newlist)
{
    beginResetModel(); // 开始重置模型，通知视图整体更新
    vipList=std::move(newlist);
    endResetModel();
}

void VipTable::setEditableFalse()
{
    isEditable=false;
}
