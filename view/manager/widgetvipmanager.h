#ifndef WIDGETVIPMANAGER_H
#define WIDGETVIPMANAGER_H

#include <QWidget>
#include"controller/services/viptableservice.h"
#include<controller/database/sqlvip.h>
namespace Ui {
class WidgetVipManager;
}

class WidgetVipManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetVipManager(QWidget *parent = nullptr);
    ~WidgetVipManager();

    void loadModelVip();
    void pushButtonInit();

private slots:
    void sortByColumn(int column);

    void on_pushButtonName_clicked(bool checked);

    void on_pushButtonSearch_clicked();

    void on_pushButtonRegTime_clicked(bool checked);

    void on_pushButtonPhoneNum_clicked(bool checked);

    void on_pushButtonPoint_clicked(bool checked);

    void on_pushButtonLevel_clicked(bool checked);

    void on_currentPage_valueChanged(int arg1);

    void on_fontpage_clicked();

    void on_prepage_clicked();

    void on_nextpage_clicked();

    void on_tailpage_clicked();

private:
    Ui::WidgetVipManager *ui;
    VipTableService * p_viptableservice;

    bool SearchName=false;
    bool SearchPhoNum=false;
    bool SearchPoint=false;
    bool SearchLev=false;
    bool SearchDate=false;
};

#endif // WIDGETVIPMANAGER_H
