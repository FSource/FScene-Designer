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
	ma_renameLayer2D=m_menuLayer2D->addAction("Rename Layer2D");
	ma_exportLayer2DFst=m_menuLayer2D->addAction("Export *.fst");

	/* --entity 2d --*/
	m_menuEntity2D=new QMenu(this);
	ma_renameEntity2D=m_menuEntity2D->addAction("Rename");
	ma_exportEntity2D=m_menuEntity2D->addAction("Export *.fst");

	ma_moveDownEntity2D=m_menuEntity2D->addAction("Move Down");
	ma_moveUpEntity2D=m_menuEntity2D->addAction("Move Up");
	ma_moveFrontEntity2D=m_menuEntity2D->addAction("Move Front");
	ma_moveTailEntity2D=m_menuEntity2D->addAction("Move Tail");

}

void SnProjectExploreWidget::connectSignal()
{
	connect(m_projectExploreView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(clicked(const QModelIndex&)));
	connect(m_projectExploreView,SIGNAL(pressed(const QModelIndex&)),this,SLOT(mousePress(const QModelIndex&)));

	//connect(ma_newLayer2D,SIGNAL(triggered()),SnGlobal::uiOperator(),SLOT(addLayer2D));
	connect(ma_renameScene,SIGNAL(triggered()),SnGlobal::uiOperator(),SLOT(renameScene()));
	connect(ma_newLayer2D,SIGNAL(triggered()),SnGlobal::uiOperator(),SLOT(addLayer2D()));


}



void SnProjectExploreWidget::clicked(const QModelIndex& index)
{
	if(!index.isValid())
	{
		return ;
	}

	SnIdentify* idfier=(SnIdentify*)index.internalPointer();
	if(m_projectExploreView->selectionModel()->currentIndex()!=index)
	{
		idfier=NULL;
	}

	if(dynamic_cast<SnScene*>(idfier))
	{
		std::vector<SnIdentify*> st_ids;
		SnGlobal::dataOperator()->setIdentifyCurrentAndSelect(idfier,st_ids);
	}
	else 
	{

		QModelIndexList list=m_projectExploreView->selectionModel()->selectedIndexes();
		int size=list.size();

		std::vector<SnIdentify*> st_ids;
		for(int i=0;i<size;i++)
		{
			QModelIndex q_id=list[i];
			if(q_id.internalPointer()!=0&&q_id.column()==0)
			{
				SnIdentify* s_id=(SnIdentify*)q_id.internalPointer();
				st_ids.push_back(s_id);
			}
		}
		SnGlobal::dataOperator()->setIdentifyCurrentAndSelect(idfier,st_ids);
	}
}


void SnProjectExploreWidget::mousePress(const QModelIndex& index)
{
	if(!index.isValid())
	{
		return ;
	}

	SnIdentify* idfier=(SnIdentify*)index.internalPointer();

	if((QApplication::mouseButtons()&Qt::RightButton))
	{
		clicked(index);

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
			m_menuEntity2D->popup(QCursor::pos());
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
void SnProjectExploreWidget::slotIdentifyAdd(SnIdentify* id)
{
	m_projectExploreModel->refresh();
}

void SnProjectExploreWidget::slotIdentifyDelete(std::vector<SnIdentify*> id)
{
	m_projectExploreModel->refresh();
}


void SnProjectExploreWidget::slotCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st)
{
	m_projectExploreView->selectionModel()->clearSelection();
	m_projectExploreView->selectionModel()->clearCurrentIndex();
	

	int size=st.size();
	//QModelIndexList m_list;
	for(int i=0;i<size;i++)
	{
		SnIdentify* id=st[i];
		QModelIndex model_index=m_projectExploreModel->getIdentifyModelIndex(id);
		m_projectExploreView->selectionModel()->select(model_index,QItemSelectionModel::Select);
		//m_list->push_back(model_index);
	}


	/*
	if(id!=NULL)
	{
		m_projectExploreView->selectionModel()->setCurrentIndex(m_projectExploreModel->getIdentifyModelIndex(id),QItemSelectionModel::SelectCurrent);
	}
	else 
	{
		m_projectExploreView->selectionModel()->clearCurrentIndex();
	}
	*/


}


void SnProjectExploreWidget::destory()
{
	delete m_projectExploreView;
	m_projectExploreView=NULL;

	delete m_projectExploreModel;
	m_projectExploreModel=NULL;
}


























