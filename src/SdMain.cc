#include <QApplication>
#include "widget/SdMainWindow.h"
#include "SdGlobal.h"


int main(int argc,char** argv)
{
    QApplication app(argc,argv);
	SdGlobal::moduleInit();
    SdMainWindow* win=new SdMainWindow();
	SdGlobal::setMainWindow(win);

	win->show();
	win->setWindowTitle("FSprite Designer v2.0");
	win->showMaximized();
	return app.exec();

}

