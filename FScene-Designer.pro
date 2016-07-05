#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T23:04:26
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FScene-Designer
TEMPLATE = app

INCLUDEPATH+= src

INCLUDEPATH +=faeris/lib/libfaeris/src \
                         faeris/lib/lib3rdparty/freetype/include \
                         faeris/lib/lib3rdparty/curl/include \
                         faeris/lib/lib3rdparty/GL/include \
                         faeris/lib/lib3rdparty/libpng/include \
                                                 faeris/lib/lib3rdparty/pthread/include \

SOURCES += src/SnMain.cc\
    src/SnGlobal.cc \
    src/core/SnIdentify.cc \
    src/core/SnProject.cc \
    src/widget/SnEditViewWidget.cc \
    src/widget/SnMainWindow.cc \
    src/widget/SnProjectExploreModel.cc \
    src/widget/SnProjectExploreWidget.cc \
    src/widget/SnPropertyWidget.cc \
    src/widget/SnResourceExploreWidget.cc \
    src/SnMsgCenter.cc \
    resource/ui/aboutdialog.cpp


HEADERS  +=   src/SnGlobal.h \
    src/core/SnIdentify.h \
    src/core/SnProject.h \
    src/widget/SnEditViewWidget.h \
    src/widget/SnMainWindow.h \
    src/widget/SnProjectExploreModel.h \
    src/widget/SnProjectExploreWidget.h \
    src/widget/SnPropertyWidget.h \
    src/widget/SnResourceExploreWidget.h \
    src/SnMsgCenter.h \
    src/SnMacros.h \
    resource/ui/aboutdialog.h

RESOURCES += \
    resource/qrc/image.qrc

FORMS += \
    resource/ui/aboutdialog.ui






win32 {

        LIBS += -L$$PWD/faeris/lib/library/win32  -llibfaerisd   \
                -L$$PWD/faeris/lib/library/win32/3rdparty -llibcurld -lglew32 -llibpngd -lfreetype

                CONFIG +=console
}
