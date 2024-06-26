#ifndef WIDGETORDERMANAGER_H
#define WIDGETORDERMANAGER_H

#include <QWidget>

#include"view/page/pageconfig.h"
#include"controller/services/ordertableservice.h"
#include"controller/services/goodstableservice.h"
#include"controller/database/sqlorder.h"
#include"controller/database/sqlorderitem.h"
#include"controller/database/sqlvip.h"
#include<QMessageBox>
#include<QFileDialog>
#include <QFileDialog>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QVariant>
namespace Ui {
class WidgetOrderManager;
}

class WidgetOrderManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetOrderManager(QWidget *parent = nullptr);
    ~WidgetOrderManager();
    void InitBoolSearchState();
    void loadModelOrder();
    void PushButtonInit();
private:
    void InitLineEditInputMode();

private slots:
    void sortByColumn(int column);

    void on_pushButtonOrderId_clicked(bool checked);

    void on_pushButtonOrderStage_clicked(bool checked);

    void on_pushButtonCashierId_clicked(bool checked);

    void on_pushButtonUserId_clicked(bool checked);

    void on_pushButtonOrderTime_clicked(bool checked);

    void on_pushButtonTotalPrice_clicked(bool checked);

    void on_pushButtonSelect_clicked();

    void on_tableViewOrder_doubleClicked(const QModelIndex &index);

    void on_pushButtonFrontPage_clicked();

    void on_pushButtonPrevPage_clicked();

    void on_spinBoxPageJump_valueChanged(int arg1);

    void on_pushButtonNextPage_clicked();

    void on_pushButtonBackPage_clicked();

    void on_pushButtonOutPutOrder_clicked();

private:
    Ui::WidgetOrderManager *ui;
    OrderTableService *p_OrderTableService;
    GoodsTableService *p_GoodsTableService;

    bool searchOrderId=false;
    bool searchOrderTime=false;
    bool searchCashierId=false;
    bool searchUserId=false;
    bool searchOrderStage=false;
    bool searchTotalPrice=false;
    QString fillSpace(const QString &str, int width);
};

#endif // WIDGETORDERMANAGER_H
