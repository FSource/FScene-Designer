#include <QApplication>

#include "widget/SnMainWindow.h"
#include "SnGlobal.h"

#include "core/SnProject.h"

/*
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

    SnProject* proj=NULL;
	SnGlobal::moduleInit();
    SnGlobal::setProject(proj);

    SnMainWindow* win=new SnMainWindow();
	SnGlobal::setMainWindow(win);


	win->show();
    win->setWindowTitle("FScene Designer v1.0");
	win->showMaximized();

	return app.exec();

}

