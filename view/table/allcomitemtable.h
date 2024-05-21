#ifndef ALLCOMITEMTABLE_H
#define ALLCOMITEMTABLE_H

#include "model/commodityitem.h"
#include <QAbstractTableModel>

class AllComItemTable : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<QString>titles;
    QVector<CommodityItem>cilist;
public:
    explicit AllComItemTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setCItemList(QVector<CommodityItem>&&newcilist);

    CommodityItem getCListId(const QModelIndex &index);
private:
};

#endif // ALLCOMITEMTABLE_H
