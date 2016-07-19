#ifndef _SN_TRANSLATE_CONTROLLER_H_
#define _SN_TRANSLATE_CONTROLLER_H_ 

#include "SnController.h"
#include "math/FsVector2.h"


class SnTranslateController:public SnController 
{
	public:
		SnTranslateController();
		virtual ~SnTranslateController();

	public:
		virtual bool onLoad(SnEditViewWidget* view);

	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);

		virtual void onDraw(SnEditViewWidget* view);

	private:
		bool m_isTouchPress;

		bool m_moveX;
		bool m_moveY;


		Faeris::Vector2f m_start;
		Faeris::Vector2f m_lastPos;
		Faeris::Vector2f m_end;

};





#endif /*_SN_TRANSLATE_CONTROLLER_H_*/
