#-------------------------------------------------
#
# Project created by QtCreator 2013-08-14T21:30:24
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FSpriteDesigner2
TEMPLATE = app

INCLUDEPATH +=  src \


SOURCES += \
    src/SdMsgCenter.cc \
    src/SdMain.cc \
    src/SdGlobal.cc \
    src/widget/SdMainWindow.cc \
    src/widget/SdEditViewWidget.cc \
    src/widget/SdProjectExploreWidget.cc \
    src/widget/SdResourceExploreWidget.cc \
    src/widget/SdAnimationTitleBar.cc \
    src/widget/SdAnimationWidget.cc \
    src/core/SdAnimation.cc \
    src/widget/SdUiTimeLineHeader.cc \
    src/widget/SdUiButton.cc \
    src/widget/SdPainterTimeLine.cc \
    src/io/SdProjectWriter.cc \
    src/io/SdProjectLoader.cc \
    src/core/SdTimeLine.cc \
    src/core/SdSubTimeLineSet.cc \
    src/core/SdSprite.cc \
    src/core/SdProject.cc \
    src/util/SdPathUtil.cc \
    src/command/SdSpriteRemoveCommand.cc \
    src/command/SdSpriteAttrChangeCommand.cc \
    src/command/SdSpriteAddCommand.cc \
    src/command/SdHistoryStates.cc \
    src/command/SdCommand.cc \
    src/command/SdAnimationRemoveCommand.cc \
    src/command/SdAnimationAttrChangeCommand.cc \
    src/command/SdAnimationAddCommand.cc \
    src/operator/SdUiOperator.cc \
    src/operator/SdOperator.cc \
    src/operator/SdDataOperator.cc \
    src/core/SdIdentify.cc \
    src/widget/SdInputDialog.cc \
    src/widget/SdProjectExploreModel.cc \
    src/core/SdImageMgr.cc \
    src/core/SdImage.cc

HEADERS  += \
    src/SdMsgCenter.h \
    src/SdGlobal.h \
    src/widget/SdPropertyWidget.h \
    src/widget/SdMainWindow.h \
    src/widget/SdEditViewWidget.h \
    src/widget/SdAnimationWidget.h \
    src/widget/SdProjectExploreWidget.h \
    src/widget/SdResourceExploreWidget.h \
    src/SdMacros.h \
    src/widget/SdAnimationTitleBar.h \
    src/core/SdAnimation.h \
    src/widget/SdUiTimeLineHeader.h \
    src/widget/SdUiButton.h \
    src/SdConfig.h \
    src/widget/SdUiTimeLineHeader.h \
    src/widget/SdPainterTimeLine.h \
    src/io/SdProjectWriter.h \
    src/io/SdProjectLoader.h \
    src/io/SdFstExport.h \
    src/io/SdFsbExporter.h \
    src/core/SdTimeLine.h \
    src/core/SdSubTimeLineSet.h \
    src/core/SdSubTimeLine.h \
    src/util/SdPathUtil.h \
    src/command/SdSpriteRemoveCommand.h \
    src/command/SdSpriteAttrChangeCommand.h \
    src/command/SdSpriteAddCommand.h \
    src/command/SdHistoryStates.h \
    src/command/SdCommand.h \
    src/command/SdAnimationRemoveCommand.h \
    src/command/SdAnimationAttrChangeCommand.h \
    src/command/SdAnimationAddCommand.h \
    src/operator/SdUiOperator.h \
    src/operator/SdOperator.h \
    src/operator/SdIoOperator.h \
    src/operator/SdDataOperator.h \
    src/util/SdCircleQueue.h \
    src/core/SdIdentify.h \
    src/widget/SdInputDialog.h \
    src/widget/SdProjectExploreModel.h


INCLUDEPATH +=faeris/lib/libfaeris/src \
                         faeris/lib/lib3rdparty/c99/include \
                         faeris/lib/lib3rdparty/freetype/include \
                         faeris/lib/lib3rdparty/curl/include \
                         faeris/lib/lib3rdparty/GL/include \
                         faeris/lib/lib3rdparty/libpng/include \
						 faeris/lib/lib3rdparty/pthread/include \


win32 {

        LIBS += -L$$PWD/faeris/lib/library/win32  -llibfaerisd   \
                -L$$PWD/faeris/lib/library/win32/3rdparty -lcurld -lglew32 -llibpngd -lfreetype

		CONFIG +=console
}

FORMS += \
    resource/ui/input_text.ui \
    resource/ui/ResourcePreView.ui \
    resource/ui/ResourcePreView.ui \
    resource/ui/AnimationTitleBar.ui \
    resource/ui/AnimationControl.ui

RESOURCES += \
    resource/qrc/image.qrc \


