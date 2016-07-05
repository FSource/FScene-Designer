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
	m_projectExploreView->setHeaderHidden(true);
    m_projectExploreView->setIndentation(12);
	m_projectExploreModel=new SnProjectExploreModel;
	m_projectExploreView->setModel(m_projectExploreModel);

	QVBoxLayout* vlayout=new QVBoxLayout();
	vlayout->addWidget(m_projectExploreView);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);
}



void SnProjectExploreWidget::initMenu()
{
	/* ---  project  ---- */
	m_menuProject=new QMenu(this);
	ma_newSprite=m_menuProject->addAction("Add Sprite");
	ma_renameProject=m_menuProject->addAction("Rename Project");
    ma_save=m_menuProject->addAction("Save");
	ma_exportAllFst=m_menuProject->addAction("Export All *.fst");
	ma_exportAllFsk=m_menuProject->addAction("Export All *.fsk");
    ma_close=m_menuProject->addAction("close");

	/* --- sprite --- */
	m_menuSprite=new QMenu(this);
	ma_newAnimation=m_menuSprite->addAction("Add Animation");
	ma_renameSprite=m_menuSprite->addAction("Rename Sprite");
	ma_cloneSprite=m_menuSprite->addAction("Clone Sprite");
	ma_exportSpriteFst=m_menuSprite->addAction("Export *.fst");
	ma_exportSpriteFsk=m_menuSprite->addAction("Export *.fsk");
	ma_deleteSprite=m_menuSprite->addAction("Delete Sprite");

	/* -- animaition -- */
	m_menuAnimation=new QMenu(this);
	ma_renameAnimation=m_menuAnimation->addAction("Rename Animation");
	ma_cloneAnimation=m_menuAnimation->addAction("Clone Animation");
	ma_deleteAnimation=m_menuAnimation->addAction("Delete Animation");

}

void SnProjectExploreWidget::connectSignal()
{
	connect(m_projectExploreView,SIGNAL(pressed(const QModelIndex&)),this,SLOT(mousePress(const QModelIndex&)));



}



void SnProjectExploreWidget::mousePress(const QModelIndex& index)
{
	if(!index.isValid())
	{
		return ;
	}

	SnIdentify* idfier=(SnIdentify*)index.internalPointer();

	switch(idfier->getClassType())
	{
        /*
		case SD_CLASS_SPRITE:
			{
				SnSprite*  sprite= (SnSprite*)idfier;
				SnOperator::data()->setCurSprite(sprite);
				break;
			}

		case SD_CLASS_ANIMATION:
			{
				SnAnimation* anim=(SnAnimation*)idfier;
				SnOperator::data()->setCurAnimation(anim);
				break;
            }
        case SD_CLASS_PROJECT:
            break;

        default:
            assert(0);
            */
	}


	if((QApplication::mouseButtons()&Qt::RightButton))
	{

		switch(idfier->getClassType())
		{
        /*
			case SD_CLASS_PROJECT:
				{
					m_menuProject->popup(QCursor::pos());
					break;
				}
			case SD_CLASS_SPRITE:
				{
					m_menuSprite->popup(QCursor::pos());
					break;
				}
			case SD_CLASS_ANIMATION:
				{
					m_menuAnimation->popup(QCursor::pos());
					break;
				}
			default:
				assert(0);
                */
		}
	}

}
void SnProjectExploreWidget::destory()
{
	delete m_projectExploreView;
	m_projectExploreView=NULL;

	delete m_projectExploreModel;
	m_projectExploreModel=NULL;
}



void SnProjectExploreWidget::slotSpriteAttributeChange(SnSprite* /* sprite */)
{
	m_projectExploreModel->refresh();
}

void SnProjectExploreWidget::slotSpriteAdd(SnProject* /*proj*/,SnSprite* /*sprite*/)
{
	m_projectExploreModel->refresh();
}

void SnProjectExploreWidget::slotSpriteRemove(SnProject* /*proj*/,SnSprite* /*sprite*/)
{
	m_projectExploreModel->refresh();
}

void SnProjectExploreWidget::slotAnimationAttributeChange(SnAnimation* /* anim */) 
{
	m_projectExploreModel->refresh();
}


void SnProjectExploreWidget::slotAnimationAdd(SnSprite* /* sprite */,SnAnimation* /* anim */)
{
	m_projectExploreModel->refresh();
}


void SnProjectExploreWidget::slotAnimationRemove(SnSprite* /* sprite */,SnAnimation* /* anim */)
{
	m_projectExploreModel->refresh();
}






















