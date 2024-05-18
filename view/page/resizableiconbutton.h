#ifndef RESIZABLEICONBUTTON_H
#define RESIZABLEICONBUTTON_H

#include <QWidget>
#include<QToolButton>

namespace Ui {
class ResizableIconButton;
}

class ResizableIconButton : public QToolButton
{
    Q_OBJECT

public:
    explicit ResizableIconButton(QWidget *parent = nullptr);
    ~ResizableIconButton();

private:
    void resizeEvent(QResizeEvent *event) override;
    Ui::ResizableIconButton *ui;
};

#endif // RESIZABLEICONBUTTON_H
