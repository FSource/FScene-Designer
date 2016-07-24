#ifndef _SN_SCALER_CONTROLLER_H_
#define _SN_SCALER_CONTROLLER_H_ 

#include "SnController.h"


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

};





#endif /*_SN_SCALER_CONTROLLER_H_*/

