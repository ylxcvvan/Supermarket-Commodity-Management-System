#ifndef WIDGETVIPMANAGER_H
#define WIDGETVIPMANAGER_H

#include <QWidget>

namespace Ui {
class WidgetVipManager;
}

class WidgetVipManager : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetVipManager(QWidget *parent = nullptr);
    ~WidgetVipManager();

private:
    Ui::WidgetVipManager *ui;
};

#endif // WIDGETVIPMANAGER_H
