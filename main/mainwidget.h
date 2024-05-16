#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "view/page/pagemain.h"
#include "view/page/pageconfig.h"
#include "view/page/pagehelp.h"
#include"../controller/database/mysql.h"
#include<QDebug>
#include<QMouseEvent>
#include<QPaintEvent>
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
private:
    void paintEvent(QPaintEvent *event);
    void FrameLessInit();
private slots:
    void on_toolButtonMain_clicked();

    void on_toolButtontConfig_clicked();

    void on_toolButtonHelp_clicked();

    void on_pushButtonMinmize_clicked();

    void on_pushButtonMaxmize_clicked(bool checked);

    void on_pushButtonExit_clicked();

    void mousePressEvent(QMouseEvent * e);

    void mouseMoveEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent * e);


private:
    bool isAdmin;
    bool isFullSceen;
    bool isMoveAllowed;
    QPoint  originalPos;


    Ui::MainWidget *ui;
    PageMain *p_pagemain;
    PageConfig *p_pageconfig;
    PageHelp *p_pagehelp;

};
#endif // MAINWIDGET_H
