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
		virtual SnIdentify* getChildHitPoint(Faeris::Vector2f point,bool traverse);
		virtual std::vector<SnIdentify*> getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse);

		bool filterExportValue(const char* name,const Faeris::FsVariant& vs);

};

#include "SnTUiWidget.inl"

#endif /*_SN_T_UI_WIDGET_H_*/


