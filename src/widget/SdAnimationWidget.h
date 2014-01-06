#ifndef _SD_ANIMATION_WIDGET_H_
#define _SD_ANIMATION_WIDGET_H_ 

#include<QWidget>
#include "ui_AnimationControl.h"

class SdUiTimeLineHeader;
class SdTimeLineBodyUi;

class SdAnimationWidget:public QWidget
{
	public:
		SdAnimationWidget();
		~SdAnimationWidget();

	public:
		virtual void paintEvent(QPaintEvent* event);
	protected:
		void initWidget();
		void initLayout();

	private:
        SdUiTimeLineHeader* m_header;
		SdTimeLineBodyUi* m_body;
};


#endif /*_SD_ANIMATION_WIDGET_H_*/





