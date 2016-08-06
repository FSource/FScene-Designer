#include "SnRotateController.h"
#include "SnGlobal.h"
#include "core/SnIdentify.h"
#include "operator/SnDataOperator.h"
#include <QMouseEvent>
#include "util/SnUtil.h"
#include "SnThemeConfig.h"
#include "widget/SnEditViewWidget.h"


SnRotateController::SnRotateController()
{
	m_isTouchPress=false;
	m_centerPos.set(0,0);
	m_lastPos.set(0,0);
}



SnRotateController::~SnRotateController()
{

}


bool SnRotateController::onLoad(SnEditViewWidget* view)
{
	return true;
}

bool SnRotateController::onTouchBegin(SnEditViewWidget* view,QMouseEvent* event)
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

	Vector3f pos=id->getPositionInWorld();
	m_centerPos=Vector2f(pos.x,pos.y);


	float zoom=view->getZoom();
	Vector2f diff=m_start-m_centerPos;


	if(diff.length()==0)
	{
		return false;
	}


	if(diff.length()<(SnThemeConfig::ROTATE_CONTROLLER_RADIUS+SnThemeConfig::ROTATE_CONTROLLER_TRIANGLE_WIDTH)/zoom)
	{
		m_isTouchPress=true;
		return true;
	}

	return false;
}



bool SnRotateController::onTouchMove(SnEditViewWidget* view,QMouseEvent* event)
{

	if(!m_isTouchPress)
	{
		return true;
	}

	Vector2f cur_pos=view->toEditCoord(Vector2f(event->pos().x(),event->pos().y()));

	if(cur_pos.equal(m_centerPos))
	{
		return true;
	}

	float ox=m_centerPos.x;
	float oy=m_centerPos.y;

	float fx=m_lastPos.x;
	float fy=m_lastPos.y;

	float tx=cur_pos.x;
	float ty=cur_pos.y;


	float vfx=fx-ox;
	float vfy=fy-oy;

	float vtx=tx-ox;
	float vty=ty-oy;

	float dg=(vfx*vtx+vfy*vty)/(sqrt(vfx*vfx+vfy*vfy)*sqrt(vtx*vtx+vty*vty));
	if(dg>1.0f)
	{
		dg=1.0f;
	}

	if(dg<-1.0f)
	{
		dg=-1.0f;
	}


	int direction=vtx*vfy-vty*vfx<0?1:-1;

	float theta=acos(dg)/3.1415925*180.0f;
	float angle=theta*direction;


	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	if(ids.size()==0)
	{
		return false;
	}

	std::vector<SnIdentify*> ids_root=SnGlobal::dataOperator()->getSelectedIdentifyRoot();

	SnGlobal::dataOperator()->rotate(ids_root,angle);

	m_lastPos=cur_pos;
	return true;
}


bool SnRotateController::onTouchEnd(SnEditViewWidget* view,QMouseEvent* event)
{
	m_isTouchPress=false;

	return false;

}

void SnRotateController::onDraw(SnEditViewWidget* view)
{
	view->drawRotateInfo(
			SnThemeConfig::ROTATE_CONTROLLER_OUT_LINE_FOCUS_COLOR
			,0);
}






