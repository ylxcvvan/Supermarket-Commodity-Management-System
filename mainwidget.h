#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "pagemain.h"
#include "pageconfig.h"
#include "pagehelp.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr,bool isadmin=false);
    ~MainWidget();

private slots:
    void on_toolButtonMain_clicked();

    void on_toolButtontConfig_clicked();

    void on_toolButtonHelp_clicked();

private:
    bool isAdmin;

    Ui::MainWidget *ui;
    PageMain *p_pagemain;
    PageConfig *p_pageconfig;
    PageHelp *p_pagehelp;

};
#endif // MAINWIDGET_H
