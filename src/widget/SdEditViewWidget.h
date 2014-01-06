#ifndef _SD_EDIT_VIEW_WIDGET_H_
#define _SD_EDIT_VIEW_WIDGET_H_ 

#include <QGLWidget>

class SdEditViewWidget:public QGLWidget
{
	Q_OBJECT 
	public:
		SdEditViewWidget();
		~SdEditViewWidget();
};

#endif /*_SD_EDIT_VIEW_WIDGET_H_*/


