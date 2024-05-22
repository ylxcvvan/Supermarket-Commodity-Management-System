#ifndef WIDGETINVENTORYMANAGER_H
#define WIDGETINVENTORYMANAGER_H

#include <QWidget>
#include<QStandardItem>
#include<QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include"view/page/pageconfig.h"
#include"controller/services/inventorytableservice.h"
#include"controller/services/allcomitemtableservice.h"
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

private:
    void InitLineEditInputMode();
    void InitBoolSearchState();
    void PushButtonInit();
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

    void on_pushButtonFrontPage_clicked();

    void on_pushButtonPrevPage_clicked();

    void on_spinBoxPageJump_valueChanged(int arg1);

    void on_pushButtonNextPage_clicked();

    void on_pushButtonBackPage_clicked();


    void on_pushButtonInPutExcel_clicked(bool checked);



    void on_pushButtonSearchItem_clicked();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::WidgetInventoryManager *ui;

    InventoryTableService *p_InventoryTableService;
    AllComItemTableService *p_AllComItemTableService;

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
