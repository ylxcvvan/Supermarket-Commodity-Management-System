QT       += core gui
QT       +=  sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/main/main.pri)
include($$PWD/model/model.pri)
include($$PWD/view/manager/manager.pri)
include($$PWD/view/page/page.pri)
include($$PWD/view/table/table.pri)
include($$PWD/controller/database/database.pri)
include($$PWD/controller/services/services.pri)

SOURCES += \



HEADERS += \


FORMS += \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

RESOURCES += \
    images.qrc
