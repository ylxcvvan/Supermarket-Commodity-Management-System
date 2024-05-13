#ifndef PAGEHELP_H
#define PAGEHELP_H

#include <QWidget>

namespace Ui {
class PageHelp;
}

class PageHelp : public QWidget
{
    Q_OBJECT

public:
    explicit PageHelp(QWidget *parent = nullptr);
    ~PageHelp();

private:
    Ui::PageHelp *ui;
};

#endif // PAGEHELP_H
