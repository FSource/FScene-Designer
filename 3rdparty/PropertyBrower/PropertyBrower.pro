#-------------------------------------------------
#
# Project created by QtCreator 2016-07-10T22:27:57
#
#-------------------------------------------------

QT       += widgets

TARGET = PropertyBrower
TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH+=src
SOURCES += \
    src/objectcontroller.cpp \
    src/qtbuttonpropertybrowser.cpp \
    src/qteditorfactory.cpp \
    src/qtgroupboxpropertybrowser.cpp \
    src/qtpropertybrowser.cpp \
    src/qtpropertybrowserutils.cpp \
    src/qtpropertymanager.cpp \
    src/qttreepropertybrowser.cpp \
    src/qtvariantproperty.cpp

HEADERS += \
    src/objectcontroller.h \
    src/qtbuttonpropertybrowser.h \
    src/qteditorfactory.h \
    src/qtgroupboxpropertybrowser.h \
    src/qtpropertybrowser.h \
    src/qtpropertybrowserutils_p.h \
    src/qtpropertymanager.h \
    src/qttreepropertybrowser.h \
    src/qtvariantproperty.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    src/qtpropertybrowser.qrc
