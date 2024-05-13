#ifndef PAGECONFIG_H
#define PAGECONFIG_H

#include <QWidget>

namespace Ui {
class PageConfig;
}

class PageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit PageConfig(QWidget *parent = nullptr);
    ~PageConfig();

private:
    Ui::PageConfig *ui;
};

#endif // PAGECONFIG_H
