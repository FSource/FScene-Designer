#ifndef _SN_ROTATE_CONTROLLER_H_
#define _SN_ROTATE_CONTROLLER_H_ 

#include <vector>
#include "SnController.h"
#include "math/FsVector2.h"


class SnRotateController:public SnController 
{
	public:
		SnRotateController();
		virtual ~SnRotateController();

	public:
		virtual bool onLoad(SnEditViewWidget* view);

	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);
		virtual void onDraw(SnEditViewWidget* view);

	public:
		bool m_isTouchPress;

		Faeris::Vector2f m_centerPos;
		Faeris::Vector2f m_lastPos;
		Faeris::Vector2f m_start;

};


#endif /*_SN_ROTATE_CONTROLLER_H_*/
