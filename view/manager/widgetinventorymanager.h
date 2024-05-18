#ifndef WIDGETINVENTORYMANAGER_H
#define WIDGETINVENTORYMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include"controller/services/inventorytableservice.h"
namespace Ui {
class WidgetInventoryManager;
}

class WidgetInventoryManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetInventoryManager(QWidget *parent = nullptr);
    ~WidgetInventoryManager();
    void loadModel();
    void InitSetTheSearchSellByTimeAddDays(int addDays);
private:
    void InitLineEditInputMode();
    void InitBoolSearchState();
private slots:

    void sortByColumn(int column);
    void on_pushButtonSelect_clicked();

    void on_pushButtonCommodityName_clicked(bool checked);

    void on_pushButtonCommodityId_clicked(bool checked);

    void on_pushButtonSellByTime_clicked(bool checked);

    void on_pushButtonDetails_clicked(bool checked);

    void on_pushButtonCostPrice_clicked(bool checked);

    void on_pushButtonPrice_clicked(bool checked);

    void on_pushButtonAmount_clicked(bool checked);

    void on_pushButtonInventoryId_clicked(bool checked);

    void on_pushButtonCategory_clicked(bool checked);

private:
    Ui::WidgetInventoryManager *ui;

    InventoryTableService *p_InventoryTableService;


    //搜索时的勾选项
    bool SearchName;
    bool SearchSellByTime;
    bool SearchCommodityId;
    bool SearchDetails;
    bool SearchPrice;
    bool SearchCostPrice;
    bool SearchInventoryId;
    bool SearchAmount;
    bool SearchCategory;
};

#endif // WIDGETINVENTORYMANAGER_H
