#include <QLabel>
#include "SdMacros.h"
#include "widget/SdMainWindow.h"

#include "widget/SdEditViewWidget.h"
#include "widget/SdAnimationWidget.h"
#include "widget/SdProjectExploreWidget.h"
#include "widget/SdResourceExploreWidget.h"
#include "widget/SdAnimationTitleBar.h"

/*
#include "widget/SdPropertyWidget.h"
*/

SdMainWindow::SdMainWindow()
{
	initMenuBar();
	initToolBar();
	initWidget();
	initLayout();

}

SdMainWindow::~SdMainWindow()
{
}

void SdMainWindow::initToolBar()
{
	m_toolbar=new QToolBar("ToolBar");

	/* undo */
	mt_undo=new QAction(QPixmap(SD_MT_UNDO),"&Undo",this);
	m_toolbar->addAction(mt_undo);
	connect(mt_undo,SIGNAL(triggered()),this,SLOT(onUndo()));

	/* redo */
	mt_redo=new QAction(QPixmap(SD_MT_REDO),"&Redo",this);
	m_toolbar->addAction(mt_redo);
	connect(mt_redo,SIGNAL(triggered()),this,SLOT(onRedo()));


    /* ---- */
	m_toolbar->addSeparator();
	/* ---- */

	/* zoom in */
	mt_zoomIn=new QAction(QPixmap(SD_MT_ZOOM_IN),"ZoomIn",this);
	m_toolbar->addAction(mt_zoomIn);
	connect(mt_zoomIn,SIGNAL(triggered()),this,SLOT(onZoomIn()));

	/* zoom out */
	mt_zoomOut=new QAction(QPixmap(SD_MT_ZOOM_OUT),"ZoomOut",this);
	m_toolbar->addAction(mt_zoomOut);
	connect(mt_zoomOut,SIGNAL(triggered()),this,SLOT(onZoomOut()));
    addToolBar(Qt::LeftToolBarArea,m_toolbar);
}

void SdMainWindow::initMenuBar()
{
    m_menubar=menuBar();

    /*File*/
    mn_file=m_menubar->addMenu("&File");
    mn_edit=m_menubar->addMenu("&Edit");
    mn_view=m_menubar->addMenu("&View");
    mn_animation=m_menubar->addMenu("&Animation");
    mn_setting=m_menubar->addMenu("&Setting");
    mn_help=m_menubar->addMenu("&Help");


}

void SdMainWindow::initWidget()
{
	m_editViewWidget=new SdEditViewWidget;
	m_animationWidget=new SdAnimationWidget;
	m_animationDockWidget=new QDockWidget("Animation");


	m_projectExploreWidget=new SdProjectExploreWidget;
	m_projectExploreDockWidget= new QDockWidget("ProjectExplore");


	m_resourceExploreWidget=new SdResourceExploreWidget;
	m_resourceExploreDockWidget=new QDockWidget("ResourceExplore");


	/*
	   m_propertyWidget= new SdPropertyWidget;
	   */
}

void SdMainWindow::initLayout()
{
	/* set dock widget tab position */

	setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::North);
	setTabPosition(Qt::RightDockWidgetArea,QTabWidget::North);
	//setTabPosition(Qt::BottomDockWidgetArea,QTabWidget::North)

	/* Edit View */
	setCentralWidget(m_editViewWidget);

	/* Animation */
    m_animationDockWidget->setTitleBarWidget(new SdAnimationTitleBar());
    m_animationDockWidget->setWidget(m_animationWidget);

    m_animationDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    m_animationDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::BottomDockWidgetArea,m_animationDockWidget);


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
















