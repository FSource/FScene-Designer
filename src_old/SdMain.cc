#include <QApplication>
/*
#include "widget/SdMainWindow.h"
#include "SdGlobal.h"
#include "FsMacros.h"
#include "FsObject.h"
#include "test.h"


NS_FS_BEGIN
void _FsScriptExtends_Finalize(FsObject* ob){}
NS_FS_END

*/


int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    /*
    SdProject* proj=createProject();
	SdGlobal::moduleInit();
    SdGlobal::setProject(proj);

    SdMainWindow* win=new SdMainWindow();
	SdGlobal::setMainWindow(win);


	win->show();
	win->setWindowTitle("FSprite Designer v2.0");
	win->showMaximized();
    */
	return app.exec();

}

