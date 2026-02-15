QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    galleryview.cpp \
    imagecell.cpp \
    imagemodel.cpp \
    inspectorview.cpp \
    main.cpp \
    mainwindow.cpp \
    meta.cpp \
    indexationservice.cpp \
    serializationservice.cpp \
    sidebarempty.cpp \
    tabbuttonwidget.cpp \
    tabcontainer.cpp

HEADERS += \
    color.h \
    feeling.h \
    galleryview.h \
    inspectorview.h \
    imagemodel.h \
    mainwindow.h \
    imagecell.h \
    indexationservice.h \
    serializationservice.h \
    sidebarempty.h \
    tabbuttonwidget.h \
    tabcontainer.h

FORMS += \
    galleryview.ui \
    imagecell.ui \
    inspectorview.ui \
    mainwindow.ui \
    sidebarempty.ui \
    tabcontainer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
