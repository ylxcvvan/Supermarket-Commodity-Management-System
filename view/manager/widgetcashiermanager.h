#ifndef WIDGETCASHIERMANAGER_H
#define WIDGETCASHIERMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "controller/services/goodstableservice.h"
#include"controller/services/comitemtableservice.h"
#include"controller/database/sqlcommondityitem.h"
namespace Ui {
class WidgetCashierManager;
}

class WidgetCashierManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCashierManager(QWidget *parent = nullptr);
    ~WidgetCashierManager();
    void loadModel();
private:
    void findAllTableViews(QObject *parent, QVector<QTableView*> &viewList);
    void updateTotalPrice_TotalCounts();

private slots:
    void getCommodityinRightTableView(const QModelIndex &index);


    void on_lineEditCommodityId_textChanged(const QString &arg1);

    void on_pushButtonAdd_clicked();

private:
    Ui::WidgetCashierManager *ui;
    GoodsTableService *p_GoodsListService;
    ComItemTableService *p_ComItemService;
    int goodsTableRow;
    QVector<QTableView*>viewList;
    QVector<Commodity> comList;

    double totalPrice;
    double totalCount;
};

#endif // WIDGETCASHIERMANAGER_H
