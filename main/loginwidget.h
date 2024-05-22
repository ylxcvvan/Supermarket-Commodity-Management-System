#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include"controller/database/sqladmin.h"
#include"controller/database/sqlcashier.h"
#include"model/user.h"
#include"mainwidget.h"
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_pushButton_3_clicked();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void on_pushButtonCshierLogin_clicked();

    void on_pushButtonAdminLogin_clicked();

private:
    Ui::LoginWidget *ui;

    bool isMoveAllowed;
    bool isResizeAllowed; // 标志是否允许调整窗口大小
    QSize originalSize; // 用于记录调整窗口大小前的原始窗口大小
    QPoint resizeRightBottomPoint;
    QPoint  BeginMovePos;
    QPoint resizeMinLeftTopPoint;
};

#endif // LOGINWIDGET_H
