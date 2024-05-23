#ifndef PAGEHELP_H
#define PAGEHELP_H

#include <QWidget>
#include<QMessageBox>
namespace Ui {
class PageHelp;
}

class PageHelp : public QWidget
{
    Q_OBJECT

public:
    explicit PageHelp(QWidget *parent = nullptr);
    ~PageHelp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PageHelp *ui;

};

#endif // PAGEHELP_H
