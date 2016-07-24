#ifndef _SN_TRANSLATE_CONTROLLER_H_
#define _SN_TRANSLATE_CONTROLLER_H_ 

#include "SnController.h"
#include "math/FsVector2.h"
#include "SnEnums.h"


class SnTranslateController:public SnController 
{
	public:
		SnTranslateController(SN_TranslateMode mode);
		SnTranslateController();
		virtual ~SnTranslateController();

	public:
		virtual bool onLoad(SnEditViewWidget* view);


	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);

		virtual void onDraw(SnEditViewWidget* view);

	public:
		void setTranslateMode(SN_TranslateMode mode){m_mode=mode;}
		SN_TranslateMode getTranslateMode(){return m_mode;}

	private:
		bool m_isTouchPress;

		bool m_moveX;
		bool m_moveY;

		SN_TranslateMode m_mode;

		Faeris::Vector2f m_start;
		Faeris::Vector2f m_lastPos;
		Faeris::Vector2f m_end;

};





#endif /*_SN_TRANSLATE_CONTROLLER_H_*/
