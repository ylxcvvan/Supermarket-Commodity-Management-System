#ifndef WIDGETVIPMANAGER_H
#define WIDGETVIPMANAGER_H

#include <QWidget>
#include"controller/services/viptableservice.h"
#include "qdebug.h"
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
public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        qDebug() << "Cells with changed data:";
        // QAbstractTableModel *model = p_viptableservice->getTable();
        // for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
        //     for (int column = topLeft.column(); column <= bottomRight.column(); ++column) {
        //         QVariant newValue = topLeft.model()->data(topLeft, Qt::DisplayRole);
        //         QModelIndex index = model->index(row,column);
        //         qDebug()<<model->index(row,column);
        //         model->setData(index,newValue);

        //     }
        // }
    }
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

    void on_pushButtonAdd_clicked(bool checked);

    void on_pushButton_clicked();

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
