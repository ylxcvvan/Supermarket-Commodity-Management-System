#include "allcomitemtable.h"

AllComItemTable::AllComItemTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"名称","描述","类别"};
}

QVariant AllComItemTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}

int AllComItemTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return cilist.size();
}

int AllComItemTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return titles.size();
}

QVariant AllComItemTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {
        const CommodityItem& item=cilist[index.row()];
        if(index.column()==0)
            return  item.getName();
        else if(index.column()==1)
            return item.getDetails();
        else
            return item.getCategory();
    }
    return QVariant();
}

void AllComItemTable::setCItemList(QVector<CommodityItem> &&newcilist)
{
    beginResetModel();
    cilist = std::move(newcilist);
    endResetModel();
}

CommodityItem AllComItemTable::getCListId(const QModelIndex &index)
{
    return cilist[index.row()];
}
