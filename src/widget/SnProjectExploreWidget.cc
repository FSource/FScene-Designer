#include <assert.h>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include "core/SnProject.h"
#include "widget/SnProjectExploreWidget.h"
#include "widget/SnProjectExploreModel.h"
#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"
#include "core/SnEntity2D.h"
#include "operator/SnDataOperator.h"
#include "operator/SnUiOperator.h"


NS_FS_USE

SnProjectExploreWidget::SnProjectExploreWidget()
{
	m_projectExploreView=NULL;
	m_projectExploreModel=NULL;

	initWidget();
	initMenu();
	connectSignal();
}



SnProjectExploreWidget::~SnProjectExploreWidget()
{
	destory();
}



void SnProjectExploreWidget::initWidget()
{
	m_projectExploreView=new QTreeView(this);
	
	m_projectExploreModel=new SnProjectExploreModel;
	
	m_projectExploreView->setModel(m_projectExploreModel);
	m_projectExploreView->setSelectionMode(QAbstractItemView::ExtendedSelection);



	m_projectExploreView->setIconSize(QSize(20,20));
	//m_projectExploreView->setHeaderHidden(true);
	m_projectExploreView->setIndentation(12);
	m_projectExploreView->setColumnWidth(1,60);
	m_projectExploreView->setColumnWidth(0,180);
	m_projectExploreView->setDragEnabled(true);
	m_projectExploreView->setAcceptDrops(true);
	m_projectExploreView->setDragDropMode(QAbstractItemView::InternalMove);



	QVBoxLayout* vlayout=new QVBoxLayout();
	vlayout->addWidget(m_projectExploreView);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);
}



void SnProjectExploreWidget::initMenu()
{
	/* ---  project  ---- */
	m_menuScene=new QMenu(this);

	ma_newLayer2D=m_menuScene->addAction("Add Layer2D");
	ma_renameScene=m_menuScene->addAction("Rename Scene");
	ma_exportSceneFst=m_menuScene->addAction("Export Scene *.fst");

	/* --- layer2D--- */
	m_menuLayer2D=new QMenu(this);
	ma_newEntity=m_menuLayer2D->addAction("Add Entity");
	ma_renameLayer2D=m_menuLayer2D->addAction("Rename Layer2D");
	ma_cloneLayer2D=m_menuLayer2D->addAction("Clone Layer2D");
	ma_exportLayer2DFst=m_menuLayer2D->addAction("Export *.fst");
	ma_deleteLayer2D=m_menuLayer2D->addAction("Delete Layer2D");

}

void SnProjectExploreWidget::connectSignal()
{
	connect(m_projectExploreView,SIGNAL(pressed(const QModelIndex&)),this,SLOT(mousePress(const QModelIndex&)));

	//connect(ma_newLayer2D,SIGNAL(triggered()),SnGlobal::uiOperator(),SLOT(addLayer2D));
	connect(ma_renameScene,SIGNAL(triggered()),SnGlobal::uiOperator(),SLOT(renameScene()));
	connect(ma_newLayer2D,SIGNAL(triggered()),SnGlobal::uiOperator(),SLOT(addLayer2D()));


}



void SnProjectExploreWidget::mousePress(const QModelIndex& index)
{
	if(!index.isValid())
	{
		return ;
	}

	SnIdentify* idfier=(SnIdentify*)index.internalPointer();

	if(dynamic_cast<SnScene*>(idfier))
	{
		/*TODO(set current)*/
	}
	else if(dynamic_cast<SnLayer2D*>(idfier))
	{
		SnGlobal::dataOperator()->setCurLayer(dynamic_cast<SnLayer2D*>(idfier));
	}
	else if(dynamic_cast<Entity2D*>(idfier))
	{
		SnGlobal::dataOperator()->setCurEntity(dynamic_cast<Entity2D*>(idfier));
	}



	if((QApplication::mouseButtons()&Qt::RightButton))
	{
		if(dynamic_cast<SnScene*>(idfier))
		{
			m_menuScene->popup(QCursor::pos());
		}
		
		else if(dynamic_cast<SnLayer2D*>(idfier))
		{
			m_menuLayer2D->popup(QCursor::pos());
		}
		else if(dynamic_cast<Entity2D*>(idfier))
		{

		}
	}

}


void SnProjectExploreWidget::onProjectChange()
{
	m_projectExploreModel->refresh();
}

void SnProjectExploreWidget::slotLayer2DAdd(SnLayer2D* ly)
{
	m_projectExploreModel->refresh();
}

void SnProjectExploreWidget::slotCurLayerChange(SnLayer2D* ly)
{
	//m_projectExploreView->selectionModel()->reset();
}

void SnProjectExploreWidget::destory()
{
	delete m_projectExploreView;
	m_projectExploreView=NULL;

	delete m_projectExploreModel;
	m_projectExploreModel=NULL;
}


























