#include "mainwidget.h"

#include <QApplication>
#include<qfile.h>
#include<qtextstream.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QFile file(":/resource/qss/style.qss");
    // if (file.open(QFile::ReadOnly)) {
    //     QString styleSheet = QLatin1String(file.readAll());
    //     qApp->setStyleSheet(styleSheet);
    //     file.close();
    // }
    MainWidget w;
    w.show();
    return a.exec();
}
