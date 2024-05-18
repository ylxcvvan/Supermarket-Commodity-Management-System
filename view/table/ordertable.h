#ifndef ORDERTABLE_H
#define ORDERTABLE_H

#include <QAbstractTableModel>

class OrderTable : public QAbstractTableModel
{
    Q_OBJECT
private:

    QVector<QString>titles;
    //
    QVector<QVector<QVariant>>ordList;

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

    void setOrdList(QVector<QVector<QVariant>>&& newlist);
private:
};

#endif // ORDERTABLE_H
