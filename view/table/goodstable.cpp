#include "goodstable.h"
#include "qdatetime.h"

#include<QDebug>
void GoodsTable::showContextMenu(const QPoint &globalPos) {
    QMenu menu;
    QAction *action1 = menu.addAction("删除");

    // 处理右键菜单项点击事
    connect(action1, &QAction::triggered, this, []() {
        qDebug() << "Action 1 triggered";
    });


    menu.exec(globalPos);
}

bool GoodsTable::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::ContextMenu) {
        // 在右键菜单事件中显示右键菜单
        QContextMenuEvent *contextMenuEvent = static_cast<QContextMenuEvent*>(event);
        showContextMenu(contextMenuEvent->globalPos());
        return true;
    }
    return QAbstractTableModel::eventFilter(obj, event);
}

GoodsTable::GoodsTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"商品编号","商品名称","商品保质期","商品单价","商品数量","商品总价"};
    this->installEventFilter(this);
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

bool GoodsTable::insertRows(int row, int count,QVector<QVector<QVariant>> newrow,const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        if (i < newrow.size()) {
            glist.insert(row, newrow[i]); // 插入新数据
        } else {
            QVector<QVariant> newRow(titles.size()); // 初始化空行
            glist.insert(row, newRow);
        }
    }
    endInsertRows();
    return true;
}

// bool GoodsTable::insertRows(int row, int count, const QModelIndex &parent)
// {
//     beginInsertRows(parent, row, row + count - 1);

//     for (int i = 0; i < count; ++i) {
//         QVector<QVariant> newRow(titles.size()); // 初始化一行，包含与列数相同数量的默认值

//         glist.insert(row, newRow);
//     }
//     endInsertRows();
//     return true;
// }

bool GoodsTable::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || count <= 0 || row + count > glist.size()) {
        return false;  // 检查参数是否有效
    }

    beginRemoveRows(parent, row, row + count - 1);

    // 从数据模型中删除指定行
    for (int i = 0; i < count; ++i) {
        glist.removeAt(row);
    }

    endRemoveRows();
    return true;
}

void GoodsTable::setGoodsList(QVector<QVector<QVariant> > &&newlist)
{
    beginResetModel();
    glist=std::move(newlist);
    endResetModel();
}

QVector<QVector<QVariant> > GoodsTable::getGoodsList()
{
    return glist;
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

}

void GoodsTable::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);
    QModelIndexList selectedRows = selected.indexes();
    for (const QModelIndex &index : selectedRows) {
        qDebug() << "Selected row index:" << index.row();
    }
}
