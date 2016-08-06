#ifndef _SN_T_UI_WIDGET_H_
#define _SN_T_UI_WIDGET_H_ 

#include "SnTEntity2D.h"

template<class T>
class  TSnUiWidget:public  TSnEntity2D<T> 
{
	public:
		virtual SnAttrGroupList* getAttributeList();
		virtual SnIdentify* getIdentifyParent();

		virtual std::vector<std::string> getObjectFstAttrList();
};

#include "SnTUiWidget.inl"

#endif /*_SN_T_UI_WIDGET_H_*/


