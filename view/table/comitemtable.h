#ifndef COMITEMTABLE_H
#define COMITEMTABLE_H

#include <QAbstractItemModel>
#include<QTextDocument>
#include"model/commodityitem.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include "model/commodityitem.h"
class ComItemTable : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<CommodityItem>cilist;
    const int ColumnShowNum=3;
public:
    explicit ComItemTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    void setCItemList(QVector<CommodityItem>&&newcilist);

private:
};


class ComItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COMITEMTABLE_H
