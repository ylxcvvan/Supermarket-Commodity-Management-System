#include "comitemtable.h"
#include "qdebug.h"

ComItemTable::ComItemTable(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant ComItemTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return QString("Column %1").arg(section + 1);
    } else {
        return QString("Row %1").arg(section + 1);
    }
}

int ComItemTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return (cilist.size() + ColumnShowNum - 1) / ColumnShowNum;
}

int ComItemTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ColumnShowNum;
}

QVariant ComItemTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int dataIndex = index.row() * ColumnShowNum + index.column();
    if (dataIndex >= cilist.size())
        return QVariant();
    if (role == Qt::DisplayRole) {
        const CommodityItem &item = cilist[dataIndex];

        return QString("物品id:%1\n物品名称：%2\n\n物品描述：%3")
            .arg(item.getItemId())
            .arg(item.getName())
            .arg(item.getDetails());

    }

    return QVariant();
}

bool ComItemTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Implement this method if needed
    return false;
}

bool ComItemTable::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // for (int i = 0; i < count; ++i) {
    //     cilist.insert(row * ColumnShowNum, CommodityItem());
    // }
    endInsertRows();
    return true;
}

bool ComItemTable::insertColumns(int column, int count, const QModelIndex &parent)
{
    // Not needed for this example
    return false;
}

bool ComItemTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        cilist.removeAt(row * ColumnShowNum);
    }
    endRemoveRows();
    return true;
}

bool ComItemTable::removeColumns(int column, int count, const QModelIndex &parent)
{
    // Not needed for this example
    return false;
}

void ComItemTable::setCItemList(QVector<CommodityItem> &&newcilist)
{
    beginResetModel();
    cilist = std::move(newcilist);
    endResetModel();
}

int ComItemTable::getCListId(const QModelIndex &index)
{
    if (!index.isValid())
        return -1;
    return cilist[index.row() * ColumnShowNum + index.column()].getItemId();
}
void ComItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();

        // 绘制背景
        painter->setRenderHint(QPainter::Antialiasing);
        QRectF rect = option.rect;
        qreal radius = 30; // 圆角半径
        painter->setBrush(QColor("#cceeff"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(rect, radius, radius);

        // 获取数据
        QString text = index.data(Qt::DisplayRole).toString();

        // 绘制文本
        painter->setPen(QPen(Qt::black));
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignTop); // 文本对齐靠上
        //BUG:重复绘图
        // painter->drawText(rect.adjusted(5, 5, -5, -5), text, textOption);

        painter->restore();
    }
    QStyledItemDelegate::paint(painter, option, index);
}

QSize ComItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(300, 300); // 自定义单元格大小
}
