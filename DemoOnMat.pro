
QT       += core gui sql webenginewidgets httpserver widgets quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    category.cpp \
    category_0_0.cpp \
    connectiondialog.cpp \
    controller.cpp \
    databasecontroller.cpp \
    datatransfercontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp

HEADERS += \
    category.h \
    category_0_0.h \
    connectiondialog.h \
    controller.h \
    databasecontroller.h \
    datatransfercontroller.h \
    mainwindow.h \
    server.h

FORMS += \
    connectiondialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
