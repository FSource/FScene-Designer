#include "SnTranslateController.h"
#include "SnGlobal.h"
#include "core/SnIdentify.h"
#include "operator/SnDataOperator.h"
#include <QMouseEvent>
#include "util/SnUtil.h"
#include "SnThemeConfig.h"
#include "widget/SnEditViewWidget.h"

NS_FS_USE
SnTranslateController::SnTranslateController()
{
	m_isTouchPress=false;
	m_start.set(0,0);
	m_lastPos.set(0,0);
	m_end.set(0,0);
}

SnTranslateController::~SnTranslateController()
{
}


bool SnTranslateController::onLoad(SnEditViewWidget* view)
{
//	m_isTouchPress=false;
	return true;
}

bool SnTranslateController::onTouchBegin(SnEditViewWidget* view,QMouseEvent* event)
{
	
	if(!(event->buttons()&Qt::LeftButton))
	{
		return false;
	}


	m_start=view->toEditCoord(Vector2f(event->pos().x(),event->pos().y()));
	m_lastPos=m_start;

	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	if(ids.size()==0)
	{
		return false;
	}
	SnIdentify* id=ids[0];

	float zoom=view->getZoom();


	if(SnUtil::hitIdentityCenterPoint(id,m_start,SnThemeConfig::TRANSLATE_CONTROLLER_CENTER_POINT_HIT_GAP/zoom))
	{
		m_moveX=true;
		m_moveY=true;
		m_isTouchPress=true;
		return true;
	}
	else if(SnUtil::hitIdentityAxisX(id, m_start,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_WIDTH/zoom,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_LONG/zoom)) 
	{
		m_moveX=true;
		m_moveY=false;
		m_isTouchPress=true;
		return true;
	}
	else if(SnUtil::hitIdentityAxisY(id,m_start,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_WIDTH/zoom,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_LONG/zoom))
	{
		m_moveX=false;
		m_moveY=true;
		m_isTouchPress=true;
		return true;
	}
	return false;
}




bool SnTranslateController::onTouchMove(SnEditViewWidget* view,QMouseEvent* event)
{
	if(!m_isTouchPress)
	{
		return true;
	}

	Vector2f cur_pos=view->toEditCoord(Vector2f(event->pos().x(),event->pos().y()));

	float diff_x =cur_pos.x-m_lastPos.x;
	float diff_y= cur_pos.y-m_lastPos.y;

	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	if(ids.size()==0)
	{
		return false;
	}
	SnIdentify* id=ids[0];

	id->translateInWorld(diff_x,diff_y);
	m_lastPos=cur_pos;

	return true;
}


bool SnTranslateController::onTouchEnd(SnEditViewWidget* view,QMouseEvent* event)
{
	m_isTouchPress=false;
	m_moveX=false;
	m_moveY=false;

	return false;
}


void SnTranslateController::onDraw(SnEditViewWidget* view)
{
	view->drawTranslateInfo(SnThemeConfig::TRANSLATE_CONTROLLER_CENTER_POINT_COLOR_ONFOCUS);
}





