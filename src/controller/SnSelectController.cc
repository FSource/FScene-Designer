

#include <QWheelEvent>
#include <QMouseEvent>

#include "widget/SnEditViewWidget.h"

#include "SnSelectController.h"
#include "util/SnRenderUtil.h"
#include "SnGlobal.h"
#include "operator/SnDataOperator.h"
#include "core/SnIdentify.h"
#include "core/SnLayer2D.h"


NS_FS_USE

SnSelectController::SnSelectController()
{
	m_isTouchPress=false;
	m_isMulSelect=false;
	m_start=Vector2f(0,0);
	m_end=Vector2f(0,0);
}

SnSelectController::~SnSelectController()
{

}

bool SnSelectController::onLoad(SnEditViewWidget* view)
{
	m_isTouchPress=false;
	m_selectedSet.clear();
	m_isMulSelect=false;
	return true;
}

bool SnSelectController::onTouchBegin(SnEditViewWidget* view,QMouseEvent* event)
{
	float x=event->pos().x();
	float y=event->pos().y();

	if(event->buttons()&Qt::LeftButton)
	{
		m_isTouchPress=true;
		m_selectedSet.clear();
		m_isMulSelect=false;
		m_start.set(x,y);
		return true;
	}

	return false;
}

bool SnSelectController::onTouchMove(SnEditViewWidget* view,QMouseEvent* event)
{
	float x=event->pos().x();
	float y=event->pos().y();


	if(!m_isTouchPress)
	{
		return true;
	}


	if(abs(m_start.x-x)> SN_SELECT_MUL_GAP || abs(m_start.y-y)>SN_SELECT_MUL_GAP) 
	{
		m_isMulSelect =true;
	}

	m_end.set(x,y);

	if(m_isMulSelect)
	{
		findIndentifyInArea(view,m_start,m_end);
	}
	return true;

}

bool SnSelectController::onTouchEnd(SnEditViewWidget* view,QMouseEvent* event)
{
	if(m_isMulSelect)
	{
		findIndentifyInArea(view,m_start,m_end);
		if(m_selectedSet.size()==0)
		{
			SnGlobal::dataOperator()->setIdentifyCurrentAndSelect(NULL,m_selectedSet);
		}
		else 
		{
			SnGlobal::dataOperator()->setIdentifyCurrentAndSelect(m_selectedSet[0],m_selectedSet);
		}
	}

	m_isTouchPress=false;

	return true;
}


void SnSelectController::findIndentifyInArea(SnEditViewWidget* view,Vector2f start,Vector2f end)
{

	SnIdentify* l=SnGlobal::dataOperator()->getCurrentLayer();

	if(l)
	{
		Vector2f start=view->toEditCoord(m_start);
		Vector2f end=view->toEditCoord(m_end);
		m_selectedSet=l->getChildInArea(start,end,true);
	}

}

void SnSelectController::findIndentifyInPoint(SnEditViewWidget* view,Vector2f x)
{

}

void SnSelectController::onDraw(SnEditViewWidget* view)
{
	if(!m_isMulSelect) 
	{
		int size=m_selectedSet.size();
		for(int i=0;i<size;i++)
		{
			SnIdentify* id=m_selectedSet[i];
			Entity2D* en=dynamic_cast<Entity2D*>(id);
			Matrix4* max4= en->getWorldMatrix();
			float minx,maxx,miny,maxy;
			en->getBoundSize2D(&minx,&maxx,&miny,&maxy);
			SnRenderUtil::drawRectangleFrame(max4,Vector2f(minx,miny),Vector2f(maxx,maxy),Color(100,0,0));
		}
		return;
	}

	if(!m_isTouchPress)
	{
		
		return;
	}

	Vector2f st=view->toEditCoord(m_start);
	Vector2f ed=view->toEditCoord(m_end);

	SnRenderUtil::drawRectangle(st,ed,Color(0,100,220,120));
}
















