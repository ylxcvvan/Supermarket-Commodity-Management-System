#include "resizableiconbutton.h"
#include "qevent.h"
#include "ui_resizableiconbutton.h"

ResizableIconButton::ResizableIconButton(QWidget *parent)
    : QToolButton(parent)
    , ui(new Ui::ResizableIconButton)
{
    ui->setupUi(this);

    setIconSize(sizeHint());
}

ResizableIconButton::~ResizableIconButton()
{
    delete ui;
}

void ResizableIconButton::resizeEvent(QResizeEvent *event)
{
    QToolButton::resizeEvent(event);
    int iconWidth = event->size().width() * 0.8; // 图标宽度为按钮宽度的80%
    int iconHeight = event->size().height() * 0.7; // 图标高度为按钮高度的70%
    setIconSize(QSize(iconWidth, iconHeight)); // 根据按钮大小调整图标大小
    QFont font = this->font(); // 获取按钮的当前字体
    //TODO
    //窗口向左延伸时的字体大小不匹配问题
    font.setPointSize(event->size().width() * 0.1); // 设置文字大小为按钮宽度的10%
    setFont(font); // 设置按钮的字体
}

