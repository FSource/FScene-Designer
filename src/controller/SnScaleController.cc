#include "SnScaleController.h"
#include "SnGlobal.h"
#include "core/SnIdentify.h"
#include "operator/SnDataOperator.h"
#include <QMouseEvent>
#include "util/SnUtil.h"
#include "SnThemeConfig.h"
#include "widget/SnEditViewWidget.h"


SnScaleController::SnScaleController()
{
	m_isTouchPress=false;
	m_start.set(0,0);
	m_lastPos.set(0,0);
	m_centerPos.set(0,0);
	m_moveX=false;
	m_moveY=false;
}

SnScaleController::~SnScaleController()
{

}

bool SnScaleController::onLoad(SnEditViewWidget* view)
{
	return true;
}


bool SnScaleController::onTouchBegin(SnEditViewWidget* view,QMouseEvent* event)
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


	if(SnUtil::hitIdentityCenterPoint(id,m_start,SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_HIT_GAP/zoom,SN_TranslateMode::LOCAL))
	{
		m_moveX=true;
		m_moveY=true;
		m_isTouchPress=true;
		return true;
	}
	else if(SnUtil::hitIdentityAxisX(id, m_start,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_WIDTH/zoom,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom,SN_TranslateMode::LOCAL)) 
	{
		m_moveX=true;
		m_moveY=false;
		m_isTouchPress=true;
		return true;
	}
	else if(SnUtil::hitIdentityAxisY(id,m_start,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_WIDTH/zoom,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom,SN_TranslateMode::LOCAL))
	{
		m_moveX=false;
		m_moveY=true;
		m_isTouchPress=true;
		return true;
	}
	return false;

}




bool SnScaleController::onTouchMove(SnEditViewWidget* view,QMouseEvent* event)
{

	if(!m_isTouchPress)
	{
		return true;
	}

	return true;

}

bool SnScaleController::onTouchEnd(SnEditViewWidget* view,QMouseEvent* event)
{
	return false;
}



void SnScaleController::onDraw(SnEditViewWidget* view)
{
	float lx=SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG;
	float ly=lx;

	if(m_moveX&&m_moveY)
	{
		view->drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR_ONFOCUS,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_COLOR,
				lx,
				ly
				);
	}
	else if(m_moveX&&!m_moveY)
	{
		view->drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_FOCUS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_COLOR,
				lx,
				ly
				);
	}
	else if((!m_moveX)&&m_moveY)
	{
		view->drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_FOCUS_COLOR,
				lx,
				ly
				);
	}

}





