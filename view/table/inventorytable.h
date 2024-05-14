#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QAbstractTableModel>

class InventoryTable : public QAbstractTableModel
{
    Q_OBJECT
private:

    QVector<QString>titles;
    //itable[0]=库存单号id,1=物品id,2=物品名称，3=物品数量,4=物品进价,5=物品描述,6=物品过期时间,
    QVector<QVector<QVariant>>itable;

public:
    explicit InventoryTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

};

#endif // INVENTORYTABLE_H
