#include "mainwidget.h"
#include"loginwidget.h"
#include <QApplication>
#include<qfile.h>
#include<qtextstream.h>

// #define TEST
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QFile file(":/resource/qss/style.qss");
    // if (file.open(QFile::ReadOnly)) {
    //     QString styleSheet = QLatin1String(file.readAll());
    //     qApp->setStyleSheet(styleSheet);
    //     file.close();
    // }
#ifdef TEST
    LoginWidget l;
    l.show();
#else
    MainWidget w;
    w.show();

#endif
    return a.exec();
}
