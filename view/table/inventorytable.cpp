#include "inventorytable.h"
#include "qdebug.h"

InventoryTable::InventoryTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    titles={"库存单号","商品编号","商品名称","   商品类别   ","商品描述","商品数量","商品售价","商品进价","商品保质期"};
}

QVariant InventoryTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return titles[section];
    }
    return QVariant();
}

int InventoryTable::rowCount(const QModelIndex &parent) const
{
    return inveList.size();
}

int InventoryTable::columnCount(const QModelIndex &parent) const
{
    return titles.size();
}

QVariant InventoryTable::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole)
    {
        return inveList[index.row()][index.column()];
    }

    return QVariant();
}

bool InventoryTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (data(index, role) != value) {
        int row=index.row();
        int column=index.column();
        if (!CanConvert(value, column) || value.toString() =="")
            return false;
        // 修改底层数组中的数据
        inveList[row][column] = value;

        // 发出数据变化信号，通知视图更新
        emit dataChanged(index, index, {role});

        // TODO: 更新数据库中的数据
        // 在这里调用更新数据库的函数，将新值写入数据库中
        // updateDatabase(row, col, newValue);
        return true;
    }
    return false;
}


Qt::ItemFlags InventoryTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.column() >=2&&index.column() <=6) {
        flags |= Qt::ItemIsEditable; // 添加编辑标志
    } else {
        flags &= ~Qt::ItemIsEditable; // 移除编辑标志
    }

    return flags;
}

bool InventoryTable::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    //TODO
    endInsertRows();
    return true;
}

bool InventoryTable::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    //TODO
    endRemoveRows();
    return true;
}

void InventoryTable::setInveList(QVector<QVector<QVariant>> &&newlist)
{
    beginResetModel(); // 开始重置模型，通知视图整体更新
    inveList=std::move(newlist);
    endResetModel();
}

bool InventoryTable::CanConvert(const QVariant &value, int col)
{

    if(col==5||col==6)
    {
        bool *ok=new bool;
        *ok=false;
        value.toDouble(ok);
        bool res=*ok;
        delete ok;
        return res;
    }
    if(col<5)
        return true;
    return false;
}


ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    ComBoBoxCategory={"食品类","日用品类","服装类","家电类","数码产品类","家具类","办公用具类","运动健身类","图书音像类","礼品类","其他类","未分类"};
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return QStyledItemDelegate::createEditor(parent, option, index);

    QComboBox *editor = new QComboBox(parent);
    // 在此处设置下拉框的选项
    for(auto&s:ComBoBoxCategory)
    {
        editor->addItem(s);
    }
    editor->setMaxVisibleItems(1e9);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    comboBox->setCurrentText(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     editor->setGeometry(option.rect);
}

QVector<QString> ComboBoxDelegate::getComBoBoxCategory()
{
    return ComBoBoxCategory;
}
