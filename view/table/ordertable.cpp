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
    return  std::min(pageSize, ordList.size() - currentPage * pageSize);
}

int OrderTable::columnCount(const QModelIndex &parent) const
{
    return titles.size();
}

QVariant OrderTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row() + currentPage * pageSize;
    if(role==Qt::DisplayRole && row < ordList.size() && index.column() < titles.size())
    {
        int column=index.column();
        auto &order=ordList[row];
        if(column==0)
            return order.getOrderId();
        else if(column==1)
            return order.getOrderTime().toString();
        else if(column==2)
            return order.getCashierId();
        else if(column==3)
            return order.getUserId();
        else if(column==4)
            return order.getTotalPrice();
        else if(column==5)
            return order.getPaidPrice();
        else if(column==6)
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

void OrderTable::sort(int column, Qt::SortOrder order)
{
    std::sort(ordList.begin(), ordList.end(), [column, order](const Order &a, const Order &b) {
        if (order == Qt::AscendingOrder)
        {
            if(column==0)
                return a.getOrderId()<b.getOrderId();
            else if(column==1)
                return a.getOrderTime()<b.getOrderTime();
            else if(column==2)
                return a.getCashierId()<b.getCashierId();
            else if(column==3)
                return a.getUserId()<b.getUserId();
            else if(column==4)
                return a.getTotalPrice()<b.getTotalPrice();
            else if(column==5)
                return a.getPaidPrice()<b.getPaidPrice();
            else if(column==6)
                return static_cast<int>(a.getOrderStage())<static_cast<int>(b.getOrderStage());
        }
        else
        {
            if(column==0)
                return a.getOrderId()>b.getOrderId();
            else if(column==1)
                return a.getOrderTime()>b.getOrderTime();
            else if(column==2)
                return a.getCashierId()>b.getCashierId();
            else if(column==3)
                return a.getUserId()>b.getUserId();
            else if(column==4)
                return a.getTotalPrice()>b.getTotalPrice();
            else if(column==5)
                return a.getPaidPrice()>b.getPaidPrice();
            else if(column==6)
                return static_cast<int>(a.getOrderStage())>static_cast<int>(b.getOrderStage());
        }

    });
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void OrderTable::setPageSize(int size)
{
    pageSize = size;
    emit layoutChanged();
}

void OrderTable::setCurrentPage(int page)
{
    if (page >= 0 && page < pageCount()) {
        currentPage = page;
        emit layoutChanged();
    }
}

int OrderTable::pageCount() const
{
    return (ordList.size() + pageSize - 1) / pageSize;
}

int OrderTable::currentPageNumber() const
{
    return currentPage;
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

