QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ColorService.cpp \
    defaultfilter.cpp \
    defaultorderer.cpp \
    feelingfilter.cpp \
    filterfactory.cpp \
    galleryview.cpp \
    imagecell.cpp \
    imagemodel.cpp \
    imagerenderer.cpp \
    imageviewer.cpp \
    inspectorview.cpp \
    main.cpp \
    mainwindow.cpp \
    meta.cpp \
    indexationservice.cpp \
    olderfirstorderer.cpp \
    ordererfactory.cpp \
    scoreorderer.cpp \
    starsfilter.cpp \
    tabmodel.cpp \
    serializationservice.cpp \
    sidebarempty.cpp \
    tabbuttonwidget.cpp \
    tabcontainer.cpp \
    lastmodifiedorderer.cpp

HEADERS += \
    ColorService.h \
    color.h \
    feeling.h \
    filterfactory.h \
    galleryview.h \
    ifilter.h \
    imagerenderer.h \
    imageviewer.h \
    inspectorview.h \
    imagemodel.h \
    iorderer.h \
    mainwindow.h \
    imagecell.h \
    indexationservice.h \
    ordererfactory.h \
    serializationservice.h \
    tabmodel.h \
    sidebarempty.h \
    tabbuttonwidget.h \
    tabcontainer.h

FORMS += \
    galleryview.ui \
    imagecell.ui \
    imagerenderer.ui \
    imageviewer.ui \
    inspectorview.ui \
    mainwindow.ui \
    sidebarempty.ui \
    tabcontainer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    edit-icon.png \
    eye-icon.png \
    heart-icon.png \
    image-icon.png \
    info-icon.png \
    redimension-icon.png

RESOURCES += \
    resources.qrc \
    resources.qrc
