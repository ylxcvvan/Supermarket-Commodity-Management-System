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
    void FrameLessInit();
private slots:

    void on_toolButtonHelp_clicked(bool checked);

    void on_toolButtonConfig_clicked(bool checked);

    void on_toolButtonMain_clicked(bool checked);

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
    bool isResizeAllowed; // 标志是否允许调整窗口大小
    QSize originalSize; // 用于记录调整窗口大小前的原始窗口大小
    QPoint resizeRightBottomPoint;
    QPoint  BeginMovePos;
    QPoint resizeMinLeftTopPoint;
    static constexpr int RESIZE_BORDER_WIDTH = 8;

    Ui::MainWidget *ui;
    PageMain *p_pagemain;
    PageConfig *p_pageconfig;
    PageHelp *p_pagehelp;

};
#endif // MAINWIDGET_H
