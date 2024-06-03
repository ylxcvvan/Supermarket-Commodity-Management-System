#ifndef WIDGETTURNOVER_H
#define WIDGETTURNOVER_H

#include "controller/services/goodstableservice.h"
#include "controller/services/ordertableservice.h"
#include <QWidget>
#include"view/page/pageconfig.h"
namespace Ui {
class widgetturnover;
}

class widgetturnover : public QWidget
{
    Q_OBJECT

public:
    explicit widgetturnover(QWidget *parent = nullptr);
    ~widgetturnover();


    void loadModelOrder();

    void gettotal_anmount();

private slots:
    void on_comboBoxRange_currentIndexChanged(int index);

    void on_pushButtonFrontPage_clicked();

    void on_pushButtonPrevPage_clicked();

    void on_spinBoxPageJump_valueChanged(int arg1);

    void on_pushButtonNextPage_clicked();

    void on_pushButtonBackPage_clicked();

private:
    Ui::widgetturnover *ui;
    OrderTableService *p_OrderTableService;
    int today = QDate::currentDate().day();
    int month = QDate::currentDate().month();
    int year = QDate::currentDate().year();
    int daysinmonth = QDate::currentDate().daysInMonth();
    int dayofweek = QDate::currentDate().dayOfWeek();
    int range;
};

#endif // WIDGETTURNOVER_H
