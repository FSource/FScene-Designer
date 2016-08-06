#ifndef _SN_CONTORLLER_H_
#define _SN_CONTORLLER_H_ 

class SnEditViewWidget;
class QMouseEvent;
class QKeyEvent;
class SnController 
{
	public:
		SnController();
		virtual ~SnController();

	public:
		virtual bool onLoad(SnEditViewWidget* view);
		virtual bool onUnload(SnEditViewWidget* view);
	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onKeyPressEvent(SnEditViewWidget* view,QKeyEvent* event);
		virtual bool onKeyReleaseEvent(SnEditViewWidget* view,QKeyEvent* event);
		virtual void onDraw(SnEditViewWidget* view);

};

#endif /*_SN_CONTORLLER_H_*/
