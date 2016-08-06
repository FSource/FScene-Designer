#include "SnResizeController.h"
#include "SnGlobal.h"
#include "core/SnIdentify.h"
#include "core/SnEntity2D.h"
#include "operator/SnDataOperator.h"
#include <QMouseEvent>
#include "util/SnUtil.h"
#include "SnThemeConfig.h"
#include "widget/SnEditViewWidget.h"


SnResizeController::SnResizeController()
{
}

SnResizeController::~SnResizeController()
{
}

bool SnResizeController::onLoad(SnEditViewWidget* view)
{

	return true;
}

bool SnResizeController::onTouchBegin(SnEditViewWidget* view,QMouseEvent* event)
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

	Entity2D* en=dynamic_cast<Faeris::Entity2D*>(id);

	float minx,maxx,miny,maxy;

	en->getBoundSize2D(&minx,&maxx,&miny,&maxy);

	Vector3f l_pos=en->worldToLocal(Vector3f(m_lastPos.x,m_lastPos.y,0));


	Vector2f  p[8]={
		Vector2f(minx,miny),
		Vector2f((minx+maxx)/2,miny),
		Vector2f(maxx,miny),
		Vector2f(maxx,(miny+maxy)/2),
		Vector2f(maxx,maxy),
		Vector2f((maxx+minx)/2,maxy),
		Vector2f(minx,maxy),
		Vector2f(minx,(miny+maxy)/2),
	};

	Matrix4* mat=en->getWorldMatrix();
	Vector3 s_info=mat->getScale();

	float gx=SnThemeConfig::RESIZE_CONTROLLER_HIT_LENGTH/zoom/s_info.x;
	float gy=SnThemeConfig::RESIZE_CONTROLLER_HIT_LENGTH/zoom/s_info.y;


	for( int i=0;i<8;i++)
	{
		float lx=l_pos.x;
		float ly=l_pos.y;

		float cx=p[i].x;
		float cy=p[i].y;


		if(Math::abs(lx-cx)<gx)
		{
			if(Math::abs(ly-cy)<gy)
			{
				m_hitPos=i;
				m_isTouchPress=true;
				return true;
			}
		}
	}

	return false;

}

bool SnResizeController::onTouchMove(SnEditViewWidget* view,QMouseEvent* event)
{
	if(!m_isTouchPress)
	{
		return true;
	}


	Vector2f cur_pos=view->toEditCoord(Vector2f(event->pos().x(),event->pos().y()));


	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	if(ids.size()==0)
	{
		return false;
	}
	SnIdentify* id=ids[0];

	Entity2D* en=dynamic_cast<Faeris::Entity2D*>(id);

	Vector3f l_pos=en->worldToLocal(Vector3f(cur_pos.x,cur_pos.y,0));

	float minx,maxx,miny,maxy;
	en->getBoundSize2D(&minx,&maxx,&miny,&maxy);

	float r_minx=1;
	float r_maxx=1 ;
	float r_miny=1;
	float r_maxy=1;

	switch(m_hitPos)
	{
		case 0:
			r_minx=l_pos.x/minx;
			r_miny=l_pos.y/miny;
			break;
		case 1:
			r_miny=l_pos.y/miny;
			break;
		case 2:
			r_maxx=l_pos.x/maxx;
			r_miny=l_pos.y/miny;
			break;

		case 3:
			r_maxx=l_pos.x/maxx;
			break;
		case 4:
			r_maxx=l_pos.x/maxx;
			r_maxy=l_pos.y/maxy;
			break;
		case 5:
			r_maxy=l_pos.y/maxy;
			break;
		case 6:
			r_minx=l_pos.x/minx;
			r_maxy=l_pos.y/maxy;
			break;

		case 7:
			r_minx=l_pos.x/minx;
			break;
	}

	SnGlobal::dataOperator()->setBoundSize2D(ids,r_minx,r_maxx,r_miny,r_maxy);

	return true;

}

bool SnResizeController::onTouchEnd(SnEditViewWidget* view,QMouseEvent* event)
{
	return false;
}

void SnResizeController::onDraw(SnEditViewWidget* view)
{
	view->drawResizeInfo(Color(),m_hitPos);

}





