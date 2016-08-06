#include <QWheelEvent>
#include <QMouseEvent>

#include "widget/SnEditViewWidget.h"
#include "SnViewMoveController.h"


SnViewMoveController::SnViewMoveController()
{
	m_isMove=false;

}


bool SnViewMoveController::onLoad(SnEditViewWidget* view)
{
	m_isMove=false;
	view->setCursor(Qt::ClosedHandCursor);
	return true;
}

bool SnViewMoveController::onUnload(SnEditViewWidget* view)
{
	view->setCursor(Qt::ArrowCursor);
	return true;
}

bool SnViewMoveController::onTouchBegin(SnEditViewWidget* /*view*/,QMouseEvent* event)
{
 	float x= event->pos().x();
	float y=  event->pos().y();
	m_lastPos.set(x,y);
	m_isMove=true;

	return true;

}

bool SnViewMoveController::onTouchMove(SnEditViewWidget* view,QMouseEvent* event)
{
	if(!m_isMove)
	{
		return true;
	}
	float x= event->pos().x();
	float y=  event->pos().y();
	float dx=x -m_lastPos.x;
	float dy=m_lastPos.y-y;

	view->translate(Vector2f(dx,dy));

	m_lastPos.set(x,y);

	return true;
}

bool SnViewMoveController::onTouchEnd(SnEditViewWidget* /*view*/,QMouseEvent* /*event*/)
{
	m_isMove=false;
	return false;
}


bool SnViewMoveController::onKeyPressEvent(SnEditViewWidget* view,QKeyEvent* event)
{
	if(event->key()==Qt::Key_Space)
	{
		return true;
	}
	return false;
}

bool SnViewMoveController::onKeyReleaseEvent(SnEditViewWidget* view,QKeyEvent* event)
{
	if(event->key()==Qt::Key_Space)
	{
		if(m_isMove)
		{
			return true;
		}

	}
	return false;
}



