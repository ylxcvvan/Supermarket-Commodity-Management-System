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
#include<QGraphicsDropShadowEffect>
#include<qtmaterialflatbutton.h>
#include"controller/database/sqlcashier.h"
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
    void setUserName(const QString& name);
private:
    void FrameLessInit();

    void WidgetTitleBtnInit();
private slots:

    void on_toolButtonHelp_clicked(bool checked);

    void on_toolButtonConfig_clicked(bool checked);

    void on_toolButtonMain_clicked(bool checked);

    void on_pushButtonMinmize_clicked();

    void on_pushButtonMaxmize_clicked(bool checked);

    void on_pushButtonExit_clicked();

    void mousePressEvent(QMouseEvent * e);

    void mouseMoveEvent(QMouseEvent * e);

    //TODO:双击标题栏放大事件
    // void mouseDoubleClickEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent * e);

    void paintEvent(QPaintEvent *event);

    void on_pushButtonLogout_clicked();

private:
    bool isAdmin;
    bool isMoveAllowed;
    bool isResizeAllowed; // 标志是否允许调整窗口大小
    QSize originalSize; // 用于记录调整窗口大小前的原始窗口大小
    QPoint resizeRightBottomPoint;
    QPoint  BeginMovePos;
    QPoint resizeMinLeftTopPoint;
    static constexpr int RESIZE_BORDER_WIDTH = 25;

    Ui::MainWidget *ui;
    PageMain *p_pagemain;
    PageConfig *p_pageconfig;
    PageHelp *p_pagehelp;



    static constexpr int layoutmargin=12;

    Qt::CursorShape getResizeCursor(bool r, bool b, bool l, bool t);
};
#endif // MAINWIDGET_H
