QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminpanel.cpp \
    databasemanager.cpp \
    depositwindow.cpp \
    featureswindow.cpp \
    loanwindow.cpp \
    main.cpp \
    mainbankgui.cpp \
    mainwindow.cpp \
    registerwin.cpp \
    settingwindow.cpp \
    transferwindow.cpp \
    withdrawwindow.cpp

HEADERS += \
    adminpanel.h \
    databasemanager.h \
    depositwindow.h \
    featureswindow.h \
    loanwindow.h \
    mainbankgui.h \
    mainwindow.h \
    registerwin.h \
    settingwindow.h \
    transferwindow.h \
    withdrawwindow.h

FORMS += \
    adminpanel.ui \
    depositwindow.ui \
    featureswindow.ui \
    loanwindow.ui \
    mainbankgui.ui \
    mainwindow.ui \
    registerwin.ui \
    settingwindow.ui \
    transferwindow.ui \
    withdrawwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
