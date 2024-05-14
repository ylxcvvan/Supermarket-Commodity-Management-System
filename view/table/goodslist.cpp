#include "goodslist.h"
#include "qdatetime.h"

#include<QDebug>
GoodsList::GoodsList(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"商品名称","商品保质期","商品数量","商品单价","商品总价","商品编号"};
    Debug();
}

QVariant GoodsList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}


int GoodsList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return glist.size();
}

int GoodsList::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return titles.size();
}

QVariant GoodsList::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {
        return glist[index.row()][index.column()];

    }
    return QVariant();
}

bool GoodsList::setData(const QModelIndex &index, const QVariant &value, int role)
{
     qDebug()<<glist;
    if (data(index, role) != value) {
        // FIXME: Implement me!
        if(!CanConvert(value,index.column()))
            return false;
        glist[index.row()][index.column()]=TypeConvert(value,index.column());
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags GoodsList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool GoodsList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool GoodsList::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

int GoodsList::getSize()
{
    return glist.size();
}

bool GoodsList::CanConvert(const QVariant &value, int col)
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

QVariant GoodsList::TypeConvert(const QVariant &value, int col)
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





void GoodsList::Debug()
{
    glist << QVector<QVariant>{"雪碧", "2024-12-31", 2.5, 10, 25.0,1001}
          << QVector<QVariant>{"可乐", "2024-12-31", 2.0, 20, 40.0,1002}
          << QVector<QVariant>{"芬达", "2024-12-31", 3.0, 15, 45.0,1003};



}
