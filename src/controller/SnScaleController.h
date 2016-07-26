#ifndef _SN_SCALER_CONTROLLER_H_
#define _SN_SCALER_CONTROLLER_H_ 

#include "SnController.h"

#include "math/FsVector2.h"
#include "SnEnums.h"



class SnScaleController:public SnController 
{
	public:
		SnScaleController();
		virtual ~SnScaleController();

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

		bool m_scaleX;
		bool m_scaleY;

		float m_scaleXRadio;
		float m_scaleYRadio;


};





#endif /*_SN_SCALER_CONTROLLER_H_*/

