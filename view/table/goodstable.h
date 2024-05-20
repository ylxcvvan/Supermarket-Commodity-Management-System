#ifndef GOODSTABLE_H
#define GOODSTABLE_H

#include <QAbstractItemModel>
#include<QVariant>
#include <QStyledItemDelegate>
class GoodsTable : public QAbstractTableModel
{
    Q_OBJECT

private:
    QVector<QString>titles;
    //glist[0]=name,1=sellbytime,2=price,3=amount,4=totalprice,5=物品的id
    QVector<QVector<QVariant>>glist;


public:
    explicit GoodsTable(QObject *parent = nullptr);

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
    bool insertRows(int row, int count,QVector<QVector<QVariant>> newrow = QVector<QVector<QVariant>>(),const QModelIndex &parent=QModelIndex());

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void setGoodsList(QVector<QVector<QVariant>>&& newlist);

    QVector<QVector<QVariant>> getGoodsList();
    int getSize();

    void setEditableFalse();

private:
    bool isEditable=true;
    bool CanConvert(const QVariant& value,int col);
    QVariant TypeConvert(const QVariant& value,int col);
    void Debug();//测试

};

#endif // GOODSTABLE_H
