#ifndef VIPTABLE_H
#define VIPTABLE_H

#include <QAbstractTableModel>
#include "model/vip.h"
#include<qvector.h>

class VipTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit VipTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    Vip getInveVipOrder(const QModelIndex &index);

    void setPageSize(int size);

    void setCurrentPage(int page);

    int pageCount() const;

    int currentPageNumber() const;

    void setVipList(QVector<Vip> &&newlist);
private:
    QVector<QString> titles;
    QVector<Vip> Vips;

    int currentPage=0;
    int pageSize=2;
};

#endif // VIPTABLE_H
