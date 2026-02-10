QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    defaultfilter.cpp \
    defaultorderer.cpp \
    galleryview.cpp \
    imagecell.cpp \
    imagemodel.cpp \
    inspectorview.cpp \
    main.cpp \
    mainwindow.cpp \
    meta.cpp \
    indexationservice.cpp \
    serializationservice.cpp \
    tabmodel.cpp

HEADERS += \
    color.h \
    feeling.h \
    galleryview.h \
    ifilter.h \
    inspectorview.h \
    imagemodel.h \
    iorderer.h \
    mainwindow.h \
    imagecell.h \
    indexationservice.h \
    serializationservice.h \
    tabmodel.h

FORMS += \
    galleryview.ui \
    imagecell.ui \
    inspectorview.ui \
    mainwindow.ui

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
