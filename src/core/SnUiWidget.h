#ifndef _SN_UI_WIDGET_H_
#define _SN_UI_WIDGET_H_ 

#include "stage/ui/FsUiWidget.h"
#include "SnTEntity2D.h"

class SnUiWidget:public TSnEntity2D<Faeris::UiWidget>
{
	public:
		SnUiWidget();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
		virtual SnAttrGroupList* getAttributeList();
		virtual SnIdentify* getIdentifyParent();

};






#endif /*_SN_UI_WIDGET_H_*/

