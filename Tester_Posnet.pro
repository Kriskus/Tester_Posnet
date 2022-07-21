QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configuration/connectionconfiguration.cpp \
    main.cpp \
    logscreen.cpp \
    mainwindow/mainwindow.cpp \
    sql/windows/sequencewindowsql.cpp \
    sql/sequencetablesql.cpp

HEADERS += \
    configuration\connectionconfiguration.h \
    logscreen.h \
    mainwindow/mainwindow.h \
    sql/windows/sequencewindowsql.h \
    sql/sequencelist.h \
    sql/sequencetablesql.h

FORMS += \
    configuration/connectionconfiguration.ui \
    logscreen.ui \
    mainwindow/mainwindow.ui \
    sql/windows/sequencewindowsql.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
