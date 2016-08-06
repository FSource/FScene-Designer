#ifndef _SN_UI_WIDGET_H_
#define _SN_UI_WIDGET_H_ 

#include "stage/ui/FsUiWidget.h"
#include "SnTUiWidget.h"

class SnUiWidget:public TSnUiWidget<Faeris::UiWidget>
{
	public:
		FS_CLASS_DECLARE(SnUiWidget);
	public:
		static SnUiWidget* newInstance(Faeris::FsDict* dict);
	public:
		SnUiWidget();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

};






#endif /*_SN_UI_WIDGET_H_*/

