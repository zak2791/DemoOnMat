
QT       += core gui sql httpserver widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    category.cpp \
    category_0.cpp \
    category_1.cpp \
    connectiondialog.cpp \
    connectionstatus.cpp \
    controller.cpp \
    controlpanel.cpp \
    controlpanel_0.cpp \
    controlpanel_1.cpp \
    databasecontroller.cpp \
    datatransfercontroller.cpp \
    item_category_0.cpp \
    item_category_1.cpp \
    ledwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp

HEADERS += \
    category.h \
    category_0.h \
    category_1.h \
    connectiondialog.h \
    connectionstatus.h \
    controller.h \
    controlpanel.h \
    controlpanel_0.h \
    controlpanel_1.h \
    databasecontroller.h \
    datatransfercontroller.h \
    item_category_0.h \
    item_category_1.h \
    ledwidget.h \
    mainwindow.h \
    server.h

FORMS += \
    connectiondialog.ui \
    controlpanel_0.ui \
    controlpanel_1.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
