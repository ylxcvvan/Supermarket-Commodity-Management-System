#ifndef PAGECONFIG_H
#define PAGECONFIG_H

#include <QWidget>
#include<QSettings>
#include<QDir>
namespace Ui {
class PageConfig;
}

class PageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit PageConfig(QWidget *parent = nullptr,bool isad=true);
    ~PageConfig();
    void setAccount(QString a);
    void setLastlogintime();
    static int getInveTableMaxRow();
    static int getAddDays();
    static int getOrdTableMaxRow();
    static int getVipTableMaxRow();
    static int getIsShowedOnTop();
    static QString getSupermarketName();
private:
    void saveSettings(const QString &key, const QVariant &value);
    QVariant loadSettings(const QString &key);
private slots:
    void on_spinBoxInveMaxShowRow_valueChanged(int arg1);

    void on_spinBoxAddDays_valueChanged(int arg1);

    void on_spinBoxOrdMaxShowRow_valueChanged(int arg1);

    void on_spinBoxVipMaxShowRow_valueChanged(int arg1);

    void on_lineEditSupermarketName_editingFinished();

    void on_checkBoxIsShowedOnTop_stateChanged(int arg1);

    void on_pushButtonChangePwd_clicked();

private:
    Ui::PageConfig *ui;
    QSettings *setting;

    QString Account;
    bool isadmin;

    //settings
    static QString SupermarketName;
    QString SupermarketNameName="SupermarketName";
    static int IsShowedOnTop;
    QString IsShowedOnTopName="IsShowedOnTop";

    //库存管理界面：
    //查询商品保质期时，默认查找days天内过期的：
    static int AddDays;
    QString AddDaysName="AddDays";
    //库存管理表格每页的最大行数
    static int InveTableMaxRow;
    QString InveTableMaxRowName="InveTableMaxRow";

    //订单管理界面:
    static int OrdTableMaxRow;
    QString OrdTableMaxRowName="OrdTableMaxRow";

    //会员管理界面：
    static int VipTableMaxRow;
    QString VipTableMaxRowName="VipTableMaxRow";

};

#endif // PAGECONFIG_H
