#include "goodstable.h"
#include "qdatetime.h"

#include<QDebug>
GoodsTable::GoodsTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"商品编号","商品名称","商品保质期","商品单价","商品数量","商品总价"};
}

QVariant GoodsTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}

int GoodsTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return glist.size();
}

int GoodsTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return titles.size();
}

QVariant GoodsTable::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {
        return glist[index.row()][index.column()];
    }
    return QVariant();
}

bool GoodsTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
     qDebug()<<glist;
    if (data(index, role) != value) {
        int row=index.row();
        int column=index.column();
        if(!CanConvert(value,column)||value.toDouble()==0)
            return false;
        glist[row][column]=value;
        glist[row][column+1]=glist[row][column-1].toDouble()*value.toDouble();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags GoodsTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    // 仅允许第4列可编辑
    if (isEditable&&index.column() == 4) {
        flags |= Qt::ItemIsEditable; // 添加编辑标志
    } else {
        flags &= ~Qt::ItemIsEditable; // 移除编辑标志
    }

    return flags;
}

bool GoodsTable::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool GoodsTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

void GoodsTable::setGoodsList(QVector<QVector<QVariant> > &&newlist)
{
    beginResetModel();
    glist=std::move(newlist);
    endResetModel();
}

int GoodsTable::getSize()
{
    return glist.size();
}

void GoodsTable::setEditableFalse()
{
    isEditable=false;
}

bool GoodsTable::CanConvert(const QVariant &value, int col)
{
    if(col==5&&value.canConvert<int>())
        return true;
    else if(col==0&&value.canConvert<QString>())
        return true;
    else if(col==1&&value.canConvert<QDate>())
        return true;
    else if((col==2||col==3||col==4)&&value.canConvert<double>())
        return true;
    return false;
}

QVariant GoodsTable::TypeConvert(const QVariant &value, int col)
{
    if(col==5)
        return value.toInt();
    else if(col==0)
        return value.toString();
    else if(col==1)
        return value.toDate();
    else
        return value.toDouble();

}

void GoodsTable::Debug()
{
    glist << QVector<QVariant>{1001,"雪碧", "2024-12-31", 2.5, 10, 25.0}
          << QVector<QVariant>{1002,"可乐", "2024-12-31", 2.0, 20, 40.0}
          << QVector<QVariant>{1003,"芬达", "2024-12-31", 3.0, 15, 45.0};
}
