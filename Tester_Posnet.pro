QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    logscreen.cpp \
    mainwindow/mainwindow.cpp \
    sql/scenariotablesql.cpp \
    sql/sequencetablesql.cpp \
    sql/testcasetablesql.cpp \
    sql/windows/tableswindoweditor.cpp

HEADERS += \
    configuration\connectionconfiguration.h \
    logscreen.h \
    mainwindow/mainwindow.h \
    sql/scenarioslist.h \
    sql/scenariotablesql.h \
    sql/sequencelist.h \
    sql/sequencetablesql.h \
    sql/testcaseList.h \
    sql/testcasetablesql.h \
    sql/windows/tableswindoweditor.h

FORMS += \
    logscreen.ui \
    mainwindow/mainwindow.ui \
    sql/windows/tableswindoweditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
