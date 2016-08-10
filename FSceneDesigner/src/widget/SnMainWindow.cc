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
#include "operator/SnUiOperator.h"
#include "operator/SnDataOperator.h"

#include "widget/SnPropertyBrowserWidget.h"
#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "SnEnums.h"


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

	/* separator */
	m_toolbar->addSeparator();

	/* edit group */
	mg_editInfo=new QActionGroup(this);



	/* edit info */
	mt_translate=new QAction(QPixmap(SN_MT_TRANSLATE),"Translate",this);
	mt_translate->setCheckable(true);
	m_toolbar->addAction(mt_translate);
	mg_editInfo->addAction(mt_translate);

	
	mt_rotate=new QAction(QPixmap(SN_MT_ROTATE),"Rotate",this);
	mt_rotate->setCheckable(true);
	m_toolbar->addAction(mt_rotate);
	mg_editInfo->addAction(mt_rotate);

	mt_scale=new QAction(QPixmap(SN_MT_SCALE),"Scale",this);
	mt_scale->setCheckable(true);
	m_toolbar->addAction(mt_scale);
	mg_editInfo->addAction(mt_scale);


	mt_resize=new QAction(QPixmap(SN_MT_RESIZE),"Resize",this);
	mt_resize->setCheckable(true);
	m_toolbar->addAction(mt_resize);
	mg_editInfo->addAction(mt_resize);



	mg_editInfo->setExclusive(true);
	mt_translate->setChecked(true);

	connect(mg_editInfo,SIGNAL(triggered(QAction* )),this,SLOT(onEditModeChange(QAction*)));

	/* separator */
	m_toolbar->addSeparator();

	/* axis info */
	mg_axis=new QActionGroup(this);

	mt_local=new QAction(QPixmap(SN_MT_AXIS_LOCAL),"Local",this);
	mt_local->setCheckable(true);
	m_toolbar->addAction(mt_local);
	mg_axis->addAction(mt_local);

	mt_world=new QAction(QPixmap(SN_MT_AXIS_WORLD),"World",this);
	mt_world->setCheckable(true);
	m_toolbar->addAction(mt_world);
	mg_axis->addAction(mt_world);

	mg_axis->setExclusive(true);
	mt_local->setChecked(true);
	connect(mg_axis,SIGNAL(triggered(QAction* )),this,SLOT(onAxisModeChange(QAction*)));

}


void SnMainWindow::initMenuBar()
{
    m_menubar=menuBar();

    /*File*/
    mn_file=m_menubar->addMenu("&File");
	{
		/* new */
		QAction* new_project=new QAction(QPixmap(SN_MT_NEW_PORJECT),"&New",this);
		mn_file->addAction(new_project);
		connect(new_project,SIGNAL(triggered()),this,SLOT(onNewProject()));


		/* open */
		QAction* open_project=new QAction(QPixmap(SN_MT_OPEN_PORJECT),"&Open",this);
		mn_file->addAction(open_project);
		connect(open_project,SIGNAL(triggered()),this,SLOT(onOpenProject()));

			/* close */
		QAction* close=new QAction(QPixmap(SN_MT_CLOSE_PORJECT),"&Close",this);
		mn_file->addAction(close);

		mn_file->addSeparator();

			/* save */
		QAction* save_project=new QAction(QPixmap(SN_MT_SAVE_PORJECT),"&Save",this);
		mn_file->addAction(save_project);
		connect(save_project,SIGNAL(triggered()),this,SLOT(onSaveProject()));

					/* save */
		QAction* save_as =new QAction(QPixmap(SN_MT_SAVE_AS_PORJECT),"&Save As",this);
		mn_file->addAction(save_as);
		
					/* save */
		QAction* export_project =new QAction(QPixmap(SN_MT_SAVE_AS_PORJECT),"&Export",this);
		mn_file->addAction(export_project);

			
		mn_file->addSeparator();

						/* exit */
		QAction* exit =new QAction(QPixmap(SN_MT_EXIT_PORJECT),"&Exit",this);
		mn_file->addAction(exit);

	}
    mn_edit=m_menubar->addMenu("&Edit");
    mn_view=m_menubar->addMenu("&View");

    mn_entity=m_menubar->addMenu("&Entity");
	{
		mn_newEntity2D=new QMenu("Create Entity2D");

		mn_entity->addMenu(mn_newEntity2D);
		{
			mf_newEntity=new QAction("Entity2D",this);
			mn_newEntity2D->addAction(mf_newEntity);

			mf_newQuad2D=new QAction("Quad2D",this);
			mn_newEntity2D->addAction(mf_newQuad2D);

			mf_newSprie2D=new QAction("Sprite2D",this);
			mn_newEntity2D->addAction(mf_newSprie2D);

			mf_newLabelTTF=new QAction("LabelTTF",this);
			mn_newEntity2D->addAction(mf_newLabelTTF);

			mf_newLabelBitmap=new QAction("LabelBitmap",this);
			mn_newEntity2D->addAction(mf_newLabelBitmap);

			mf_newParticle2D=new QAction("Particle2D",this);
			mn_newEntity2D->addAction(mf_newParticle2D);
		}
		mn_newUi=new QMenu("Create Ui");
		mn_entity->addMenu(mn_newUi);
		{
			mf_newPressButton=new QAction("PressButton",this);
			mn_newUi->addAction(mf_newPressButton);

			mf_newToggleButton=new QAction("ToggleButton",this);
			mn_newUi->addAction(mf_newToggleButton);

			mf_newProcessBar=new QAction("ProcessBar",this);
			mn_newUi->addAction(mf_newProcessBar);

			mf_newUiWidget=new QAction("UiWidget",this);
			mn_newUi->addAction(mf_newUiWidget);

			mf_newScrollView=new QAction("ScrollView",this);
			mn_newUi->addAction(mf_newScrollView);

			mf_newListView=new QAction("ListView",this);
			mn_newUi->addAction(mf_newListView);

			mf_newPageView=new QAction("PageView",this);
			mn_newUi->addAction(mf_newPageView);

			mf_newDynamicView=new QAction("DynamicView",this);
			mn_newUi->addAction(mf_newDynamicView);
		}

	}

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
	connect(SnGlobal::msgCenter(),SIGNAL(signalEditModeChange(SN_EditMode)),this,SLOT(onEditModeChange(SN_EditMode)));
	connect(SnGlobal::msgCenter(),SIGNAL(signalTranslateModeChange(SN_TranslateMode)),this,SLOT(onAxisModeChange(SN_TranslateMode)));



	m_editViewWidget=new SnEditViewWidget;
	m_editViewWidget->setAcceptDrops(true);

	connect(SnGlobal::msgCenter(), SIGNAL(signalIdentifyAttributeChange(SnIdentify*,const char* )),m_editViewWidget,SLOT(slotIdentifyAttributeChange(SnIdentify*,const char* )));
	connect(SnGlobal::msgCenter(),SIGNAL(signalCurrentAndSelectsChange(SnIdentify* ,const std::vector<SnIdentify*>& )),
			m_editViewWidget,SLOT(slotCurrentAndSelectsChange(SnIdentify* ,const std::vector<SnIdentify*>& )));

	connect(SnGlobal::msgCenter(),SIGNAL(signalEditModeChange(SN_EditMode)),m_editViewWidget,SLOT(onEditModeChange(SN_EditMode)));
	connect(SnGlobal::msgCenter(),SIGNAL(signalTranslateModeChange(SN_TranslateMode)),m_editViewWidget,SLOT(onAxisModeChange(SN_TranslateMode)));


	m_projectExploreWidget=new SnProjectExploreWidget;
	m_projectExploreDockWidget= new QDockWidget("ProjectExplore");
	connect(SnGlobal::msgCenter(),SIGNAL(signalCurProjectChange()),m_projectExploreWidget,SLOT(onProjectChange()));
	connect(SnGlobal::msgCenter(),SIGNAL(signalLayer2DAdd(SnLayer2D*)),m_projectExploreWidget,SLOT(slotLayer2DAdd(SnLayer2D*)));
	connect(SnGlobal::msgCenter(),SIGNAL(signalIdentifyAdd(SnIdentify*)),m_projectExploreWidget,SLOT(slotIdentifyAdd(SnIdentify*)));
	connect(SnGlobal::msgCenter(),SIGNAL(signalIdentifyDelete(std::vector<SnIdentify*>)),m_projectExploreWidget,SLOT(slotIdentifyDelete(std::vector<SnIdentify*>)));

	connect(SnGlobal::msgCenter(),SIGNAL(signalCurrentAndSelectsChange(SnIdentify* ,const std::vector<SnIdentify*>& )),
			m_projectExploreWidget,SLOT(slotCurrentAndSelectsChange(SnIdentify* ,const std::vector<SnIdentify*>& )));



	m_resourceExploreWidget=new SnResourceExploreWidget;
	m_resourceExploreDockWidget=new QDockWidget("ResourceExplore");
	connect(SnGlobal::msgCenter(),SIGNAL(signalCurProjectChange()),m_resourceExploreWidget,SLOT(slotCurProjectChange()));



	m_propertyWidget= new SnPropertyBrowserWidget;

	m_propertyDockWidget=new QDockWidget("PropertyBrowserExplore");
	connect(SnGlobal::msgCenter(),SIGNAL(signalCurProjectChange()),m_propertyWidget,SLOT(slotCurProjectChange()));
	connect(SnGlobal::msgCenter(), SIGNAL(signalIdentifyAttributeChange(SnIdentify*,const char* )),m_propertyWidget,SLOT(slotIdentifyAttributeChange(SnIdentify*,const char* )));
	connect(SnGlobal::msgCenter(),SIGNAL(signalCurrentAndSelectsChange(SnIdentify* ,const std::vector<SnIdentify*>& )),
			m_propertyWidget,SLOT(slotCurrentAndSelectsChange(SnIdentify* ,const std::vector<SnIdentify*>& )));
}

void SnMainWindow::initLayout()
{
	/* set dock widget tab position */

	setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::North);
	setTabPosition(Qt::RightDockWidgetArea,QTabWidget::North);
	//setTabPosition(Qt::BottomDockWidgetArea,QTabWidget::North)

	/* Edit View */
	setCentralWidget(m_editViewWidget);


	/* property Editor*/
	m_propertyDockWidget->setWidget(m_propertyWidget);
	m_propertyDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

	addDockWidget(Qt::LeftDockWidgetArea,m_propertyDockWidget);

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

/* file */
void SnMainWindow::onNewProject()
{
	SnGlobal::uiOperator()->newProject();
}

void SnMainWindow::onOpenProject()
{
	SnGlobal::uiOperator()->openProject();
}
void SnMainWindow::onSaveProject()
{
	SnGlobal::uiOperator()->saveProject();
}



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
	m_editViewWidget->onZoomIn();
}

void SnMainWindow::onZoomOut()
{
	m_editViewWidget->onZoomOut();
}



void SnMainWindow::onHelp()
{
	QDesktopServices::openUrl(QUrl("http://www.fsource.cn"));
}



void SnMainWindow::onAbout()
{
	m_aboutDialog->show();
}

void SnMainWindow::onEditModeChange(QAction* action)
{

	if(action==mt_translate)
	{
		SnGlobal::dataOperator()->setEditMode(SN_EditMode::TRANSALTE);
	}
	else if(action==mt_scale)
	{
		SnGlobal::dataOperator()->setEditMode(SN_EditMode::SCALE);
	}
	else if(action==mt_rotate)
	{
		SnGlobal::dataOperator()->setEditMode(SN_EditMode::ROTATE);
	}
	else if(action==mt_resize)
	{
		SnGlobal::dataOperator()->setEditMode(SN_EditMode::RESIZE);
	}
}

void SnMainWindow::onAxisModeChange(QAction* action)
{
	if(action==mt_world)
	{
		SnGlobal::dataOperator()->setTranslateMode(SN_TranslateMode::WORLD);
	}
	else if(action==mt_local)
	{
		SnGlobal::dataOperator()->setTranslateMode(SN_TranslateMode::LOCAL);
	}

}

void SnMainWindow::onEditModeChange(SN_EditMode mode)
{
	mg_editInfo->blockSignals(true);

	if(mode ==SN_EditMode::RESIZE)
	{
		mt_resize->setChecked(true);
	}
	else if(mode==SN_EditMode::SCALE)
	{
		mt_scale->setChecked(true);
	}
	else if(mode==SN_EditMode::TRANSALTE)
	{
		mt_translate->setChecked(true);
	}
	else if(mode==SN_EditMode::ROTATE)
	{
		mt_rotate->setChecked(true);
	}

	mg_editInfo->blockSignals(false);
}

void SnMainWindow::onAxisModeChange(SN_TranslateMode mode )
{
	mg_axis->blockSignals(true);
	if(mode==SN_TranslateMode::LOCAL)
	{
		mt_local->setChecked(true);
	}
	else if(mode==SN_TranslateMode::WORLD)
	{
		mt_world->setChecked(true);
	}

}




void SnMainWindow::createAboutDialog()
{
	/* about dialog */
	m_aboutDialog=new QDialog;
	Ui_AboutDialog ui_about;
	ui_about.setupUi(m_aboutDialog);

}












