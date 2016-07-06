#include <QApplication>

#include "widget/SnMainWindow.h"
#include "SnGlobal.h"

#include "core/SnProject.h"


#include "FsMacros.h"
#include "FsObject.h"
#include "FsFaerisModule.h"

#include "FsFaerisModule.h"
#include "FsGlobal.h"
#include "scheduler/FsScheduler.h"
#include "stage/FsDirector.h"
#include "graphics/FsRenderDevice.h"
#include "sys/event/FsTouchDispatcher.h"
#include "sys/event/FsSysDispatcher.h"
#include "sys/event/FsKeypadDispatcher.h"
#include "sys/event/FsInputTextDispatcher.h"

#include "sys/FsWindow.h"
#include "extends/FsScriptEngine.h"
#include "mgr/FsTextureMgr.h"
#include "mgr/FsFontTTFMgr.h"
#include "mgr/FsSprite2DDataMgr.h"
#include "mgr/FsProgramSourceMgr.h"

#include "sys/io/FsVFS.h"
#include "sys/io/FsPackage.h"
#include "support/util/FsDict.h"
#include "support/util/FsArray.h"
#include "support/util/FsScriptUtil.h"

NS_FS_BEGIN
void _FsScriptExtends_Finalize(FsObject* ob){}
NS_FS_END


NS_FS_USE;



int main(int argc,char** argv)
{
    QApplication app(argc,argv);

	SnGlobal::moduleInit();


    SnMainWindow* win=new SnMainWindow();
	SnGlobal::setMainWindow(win);


	SnGlobal::setProject(NULL);

	win->setMinimumSize(QSize(1280	,800));
	win->show();

    win->setWindowTitle("FScene Designer v1.0");
	win->showMaximized();

	int ret= app.exec();

	//FsFaeris_ModuleExit();
	return ret;
}

