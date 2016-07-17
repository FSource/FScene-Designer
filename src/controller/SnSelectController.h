#ifndef _SN_SELECTION_CONTROLLER_H_
#define _SN_SELECTION_CONTROLLER_H_ 

#include <vector>
#include "SnController.h"
#include "math/FsVector2.h"


class SnIdentify;
#define SN_SELECT_MUL_GAP 8

class SnSelectController:public SnController 
{
	public:
		SnSelectController();
		virtual ~SnSelectController();

	public:
		virtual bool onLoad(SnEditViewWidget* view);
	public:
		virtual bool onTouchBegin(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchMove(SnEditViewWidget* view,QMouseEvent* event);
		virtual bool onTouchEnd(SnEditViewWidget* view,QMouseEvent* event);

		virtual void onDraw(SnEditViewWidget* view);


	public:
		void findIndentifyInArea(SnEditViewWidget* view,Faeris::Vector2f start,Faeris::Vector2f end);
		void findIndentifyInPoint(SnEditViewWidget* view,Faeris::Vector2f x);

	private:
		bool m_isTouchPress;

		bool m_isMulSelect;
		Faeris::Vector2f m_start;
		Faeris::Vector2f m_end;

		std::vector<SnIdentify*> m_selectedSet;
};



#endif /* _SN_SELECTION_CONTROLLER_H_ */
