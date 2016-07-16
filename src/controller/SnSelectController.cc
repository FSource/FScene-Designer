

#include <QWheelEvent>
#include <QMouseEvent>

#include "widget/SnEditViewWidget.h"

#include "SnSelectController.h"
#include "util/SnRenderUtil.h"

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
		findIndentifyInArea(m_start,m_end);
	}
	return true;

}

bool SnSelectController::onTouchEnd(SnEditViewWidget* view,QMouseEvent* event)
{
	if(m_isMulSelect)
	{
		findIndentifyInPoint(m_start);
	}

	m_isTouchPress=false;

	return true;
}


void SnSelectController::findIndentifyInArea(Vector2f start,Vector2f end)
{

}

void SnSelectController::findIndentifyInPoint(Vector2f x)
{

}

void SnSelectController::onDraw(SnEditViewWidget* view)
{
	if(!m_isMulSelect) 
	{
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
















