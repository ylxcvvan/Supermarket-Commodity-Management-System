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
        int colomn=index.column();
        auto &order=ordList[index.row()];
        if(colomn==0)
            return order.getOrderId();
        else if(colomn==1)
            return order.getOrderTime().toString();
        else if(colomn==2)
            return order.getCashierId();
        else if(colomn==3)
            return order.getUserId();
        else if(colomn==4)
            return order.getTotalPrice();
        else if(colomn==5)
            return order.getPaidPrice();
        else if(colomn==6)
        {
            switch (order.getOrderStage()) {
            case Order::stage::cancelled:
                return "已取消×";
            case Order::stage::Completed:
                return "已完成√";
            case Order::stage::Pending:
                return "待付款-";
                break;
            }
        }
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

void OrderTable::setOrdList(QVector<Order> &&newlist)
{
    beginResetModel(); // 开始重置模型，通知视图整体更新
    ordList=std::move(newlist);
    endResetModel();
}

Order OrderTable::getInveListOrder(const QModelIndex &index)
{
    return ordList[index.row()];
}

