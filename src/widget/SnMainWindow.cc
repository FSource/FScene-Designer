#include <QLabel>
#include <QtGlobal>
#include <QUrl>
#include <QDesktopServices>
#include "SnMacros.h"
#include "widget/SnMainWindow.h"
#include "ui_aboutdialog.h"
#include "widget/SnEditViewWidget.h"
#include "widget/SnProjectExploreWidget.h"
#include "widget/SnResourceExploreWidget.h"
//#include "operator/SnOperator.h"
//#include "operator/SnDataOperator.h"

#include "widget/SnPropertyWidget.h"

SnMainWindow::SnMainWindow()
{
	initMenuBar();
	initToolBar();
	initWidget();
	initLayout();
    createAboutDialog();

}

SnMainWindow::~SnMainWindow()
{
}

void SnMainWindow::initToolBar()
{
	m_toolbar=new QToolBar("ToolBar");

	/* undo */
    mt_undo=new QAction(QPixmap(SN_MT_UNDO),"&Undo",this);
	m_toolbar->addAction(mt_undo);
	connect(mt_undo,SIGNAL(triggered()),this,SLOT(onUndo()));

	/* redo */
    mt_redo=new QAction(QPixmap(SN_MT_REDO),"&Redo",this);
	m_toolbar->addAction(mt_redo);
	connect(mt_redo,SIGNAL(triggered()),this,SLOT(onRedo()));


    /* ---- */
	m_toolbar->addSeparator();
	/* ---- */

	/* zoom in */
    mt_zoomIn=new QAction(QPixmap(SN_MT_ZOOM_IN),"ZoomIn",this);
	m_toolbar->addAction(mt_zoomIn);
	connect(mt_zoomIn,SIGNAL(triggered()),this,SLOT(onZoomIn()));

	/* zoom out */
    mt_zoomOut=new QAction(QPixmap(SN_MT_ZOOM_OUT),"ZoomOut",this);
	m_toolbar->addAction(mt_zoomOut);
	connect(mt_zoomOut,SIGNAL(triggered()),this,SLOT(onZoomOut()));
    addToolBar(Qt::LeftToolBarArea,m_toolbar);
}

void SnMainWindow::initMenuBar()
{
    m_menubar=menuBar();

    /*File*/
    mn_file=m_menubar->addMenu("&File");
    mn_edit=m_menubar->addMenu("&Edit");
    mn_view=m_menubar->addMenu("&View");
    mn_animation=m_menubar->addMenu("&Animation");
    mn_setting=m_menubar->addMenu("&Setting");

    /* about */
    QMenu* mn_about=m_menubar->addMenu("About");
    {
        /* online toturial*/
        ms_help=new QAction(QPixmap(""),"&Online Tutorial",this);
        mn_about->addAction(ms_help);
        connect(ms_help,SIGNAL(triggered()),this,SLOT(onHelp()));

        /* about us */
        ms_about_us=new QAction(QPixmap(""),"&About Us",this);
        mn_about->addAction(ms_about_us);
        connect(ms_about_us,SIGNAL(triggered()),this,SLOT(onAbout()));
    }


}

void SnMainWindow::initWidget()
{
	m_editViewWidget=new SnEditViewWidget;



	m_projectExploreWidget=new SnProjectExploreWidget;
	m_projectExploreDockWidget= new QDockWidget("ProjectExplore");


	m_resourceExploreWidget=new SnResourceExploreWidget;
	m_resourceExploreDockWidget=new QDockWidget("ResourceExplore");


   //m_propertyWidget= new SnPropertyWidget;
}

void SnMainWindow::initLayout()
{
	/* set dock widget tab position */

	setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::North);
	setTabPosition(Qt::RightDockWidgetArea,QTabWidget::North);
	//setTabPosition(Qt::BottomDockWidgetArea,QTabWidget::North)

	/* Edit View */
	setCentralWidget(m_editViewWidget);




	/* ProjectExplore*/
	m_projectExploreDockWidget->setWidget(m_projectExploreWidget);
	m_projectExploreDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,m_projectExploreDockWidget);


	/* ResourceExplore*/
	m_resourceExploreDockWidget->setWidget(m_resourceExploreWidget);
	m_projectExploreDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,m_resourceExploreDockWidget);


	/* tabifyDockWidget */
	tabifyDockWidget(m_projectExploreDockWidget,m_resourceExploreDockWidget);

}




/* slots */

void SnMainWindow::onUndo()
{
    /*
	if(SnOperator::data()->canUndo())
    {
        qDebug("undo");
		SnOperator::data()->undo();
	}
    */

}

void SnMainWindow::onRedo()
{
    /*
	if(SnOperator::data()->canRedo())
    {
        qDebug("redo");
		SnOperator::data()->redo();
	}
    */

}

void SnMainWindow::onZoomIn()
{

}

void SnMainWindow::onZoomOut()
{

}



void SnMainWindow::onHelp()
{
  QDesktopServices::openUrl(QUrl("http://www.fsouce.cn"));
}



void SnMainWindow::onAbout()
{
    m_aboutDialog->show();
}


void SnMainWindow::createAboutDialog()
{
    /* about dialog */
    m_aboutDialog=new QDialog;
    Ui_AboutDialog ui_about;
    ui_about.setupUi(m_aboutDialog);

}










