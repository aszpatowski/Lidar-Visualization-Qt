QT       += core gui

LIBS += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exportchoice.cpp \
    exportimage.cpp \
    exportvideo.cpp \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    options.cpp

HEADERS += \
    exportchoice.h \
    exportimage.h \
    exportvideo.h \
    mainwindow.h \
    myopenglwidget.h \
    options.h

FORMS += \
    exportchoice.ui \
    exportimage.ui \
    exportvideo.ui \
    mainwindow.ui \
    options.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = icons/Lidaricon.ico
