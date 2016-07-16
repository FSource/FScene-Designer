#ifndef _SN_VIEW_MOVE_CRONTROLLER_H_
#define _SN_VIEW_MOVE_CRONTROLLER_H_ 

#include "SnController.h"
#include "math/FsVector2.h"

class SnViewMoveController:public SnController 
{
	public:
		SnViewMoveController();
	public:
		virtual bool onLoad(SnEditViewWidget* view);
		virtual bool onUnload(SnEditViewWidget* view);
	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onKeyPressEvent(SnEditViewWidget* view,QKeyEvent* event);
		virtual bool onKeyReleaseEvent(SnEditViewWidget* view,QKeyEvent* event);

	private:
		bool m_isMove;
		Faeris::Vector2f m_lastPos;
};



#endif /*_SN_VIEW_MOVE_CRONTROLLER_H_*/
