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
	m_scaleX=false;
	m_scaleY=false;
	m_scaleXRadio=1;
	m_scaleYRadio=1;

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


	m_scaleXRadio=1;
	m_scaleYRadio=1;


	m_start=view->toEditCoord(Vector2f(event->pos().x(),event->pos().y()));
	m_lastPos=m_start;


	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	if(ids.size()==0)
	{
		return false;
	}
	SnIdentify* id=ids[0];

	float zoom=view->getZoom();


	Vector3f pos=id->getPositionInWorld();
	m_centerPos=Vector2f(pos.x,pos.y);


	if(SnUtil::hitIdentityCenterPoint(id,m_start,SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_HIT_GAP/zoom,SN_TranslateMode::LOCAL))
	{
		m_scaleX=true;
		m_scaleY=true;
		m_isTouchPress=true;
		return true;
	}
	else if(SnUtil::hitIdentityAxisX(id, m_start,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_WIDTH/zoom,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom,SN_TranslateMode::LOCAL)) 
	{
		m_scaleX=true;
		m_scaleY=false;
		m_isTouchPress=true;
		return true;
	}
	else if(SnUtil::hitIdentityAxisY(id,m_start,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_WIDTH/zoom,SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom,SN_TranslateMode::LOCAL))
	{
		m_scaleX=false;
		m_scaleY=true;
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

	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	if(ids.size()==0)
	{
		return false;
	}
	SnIdentify* id=ids[0];
	std::vector<SnIdentify*> ids_root=SnGlobal::dataOperator()->getSelectedIdentifyRoot();
	float zoom=view->getZoom();

	Entity2D* en=dynamic_cast<Faeris::Entity2D*>(id);


	Vector2f cur_pos=view->toEditCoord(Vector2f(event->pos().x(),event->pos().y()));

	Vector2f v_diff=cur_pos-m_lastPos;


	if(m_scaleX&&!m_scaleY)
	{
		Vector3f t_curpos=en->worldToLocal(Vector3f(cur_pos.x,cur_pos.y,0));
		Vector3f t_lastpos=en->worldToLocal(Vector3f(m_lastPos.x,m_lastPos.y,0));
		Vector3f l_pos=t_curpos-t_lastpos;

		Vector2f t_diff=id->toXAxisProj(v_diff);
		
		float s=t_diff.length()/(SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom);
		float old_scale_radio=m_scaleXRadio;

		if(l_pos.x<0)
		{
			s=-s;
		}
	
		m_scaleXRadio+=s;


		if(old_scale_radio==0)
		{
			SnGlobal::dataOperator()->scale(ids_root,m_scaleXRadio,1);
		}
		else 
		{
			SnGlobal::dataOperator()->scale(ids_root,m_scaleXRadio/old_scale_radio,1);
		}

		if(m_scaleXRadio<0)
		{
			m_scaleXRadio=-m_scaleXRadio;
		}

	}
	else if(!m_scaleX&&m_scaleY)
	{

		Vector3f t_curpos=en->worldToLocal(Vector3f(cur_pos.x,cur_pos.y,0));
		Vector3f t_lastpos=en->worldToLocal(Vector3f(m_lastPos.x,m_lastPos.y,0));
		Vector3f l_pos=t_curpos-t_lastpos;

		Vector2f t_diff=id->toYAxisProj(v_diff);
		
		float s=t_diff.length()/(SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom);
		float old_scale_radio=m_scaleYRadio;

		if(l_pos.y<0)
		{
			s=-s;
		}
	
		m_scaleYRadio+=s;


		if(old_scale_radio==0)
		{
			SnGlobal::dataOperator()->scale(ids_root,1,m_scaleYRadio);
		}
		else 
		{
			SnGlobal::dataOperator()->scale(ids_root,1,m_scaleYRadio/old_scale_radio);
		}

		if(m_scaleYRadio<0)
		{
			m_scaleYRadio=-m_scaleYRadio;
		}
	}
	else 
	{

		Vector3f t_curpos=en->worldToLocal(Vector3f(cur_pos.x,cur_pos.y,0));
		Vector3f t_lastpos=en->worldToLocal(Vector3f(m_lastPos.x,m_lastPos.y,0));
		Vector3f l_pos=t_curpos-t_lastpos;

		float s=v_diff.length()/(SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG/zoom);


		float old_scalex_radio=m_scaleXRadio;
		float old_scaley_radio=m_scaleYRadio;

		if(l_pos.x<0)
		{
			s=-s;
		}

		m_scaleXRadio+=s;
		m_scaleYRadio+=s;



		if(old_scalex_radio==0)
		{
			old_scalex_radio=1;
		}

		if(old_scaley_radio==0)
		{
			old_scaley_radio=1;
		}

		SnGlobal::dataOperator()->scale(ids_root,m_scaleXRadio/old_scalex_radio,m_scaleYRadio/old_scaley_radio);

		if(m_scaleYRadio<0)
		{
			m_scaleYRadio=-m_scaleYRadio;
		}
		if(m_scaleXRadio<0)
		{
			m_scaleXRadio=-m_scaleXRadio;
		}



	}
	m_lastPos=cur_pos;

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

	if(m_scaleX&&m_scaleY)
	{
		view->drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR_ONFOCUS,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_COLOR,
				lx*m_scaleXRadio,
				ly*m_scaleYRadio
				);
	}
	else if(m_scaleX&&!m_scaleY)
	{
		view->drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_FOCUS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_COLOR,
				lx*m_scaleXRadio,
				ly*m_scaleYRadio
				);
	}
	else if((!m_scaleX)&&m_scaleY)
	{
		view->drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_FOCUS_COLOR,
				lx*m_scaleXRadio,
				ly*m_scaleYRadio
				);
	}

}





