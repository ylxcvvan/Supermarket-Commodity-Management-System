#ifndef ORDERTABLE_H
#define ORDERTABLE_H

#include <QAbstractTableModel>
#include"model/order.h"
class OrderTable : public QAbstractTableModel
{
    Q_OBJECT
private:

    QVector<QString>titles;
    QVector<Order>ordList;

    int currentPage=0;
    int pageSize=10;

public:
    explicit OrderTable(QObject *parent = nullptr);

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

    //排序
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    void setOrdList(QVector<Order>&& newlist);

    Order getInveListOrder(const QModelIndex &index);


    void setCurrentPage(int page);
    void setPageSize(int size);
    int pageCount() const;
    int currentPageNumber() const;
private:
};

#endif // ORDERTABLE_H
