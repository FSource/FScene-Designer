#ifndef _SN_RESIZE_CONTROLLER_H_
#define _SN_RESIZE_CONTROLLER_H_ 

#include <vector>
#include "SnController.h"
#include "math/FsVector2.h"

class SnResizeController:public SnController 
{
	public:
		SnResizeController();
		virtual ~SnResizeController();

	public:
		virtual bool onLoad(SnEditViewWidget* view);


	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);
		virtual void onDraw(SnEditViewWidget* view);

	public:
		bool m_isTouchPress;
		int m_hitPos;
		Faeris::Vector2f m_lastPos;
		Faeris::Vector2f m_start;
};

#endif /*_SN_RESIZE_CONTROLLER_H_*/

