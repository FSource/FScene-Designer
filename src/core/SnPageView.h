#ifndef _SN_PAGE_VIEW_H_
#define _SN_PAGE_VIEW_H_ 

#include "stage/ui/FsPageView.h"
#include "SnTEntity2D.h"

class SnPageView:public TSnEntity2D<Faeris::PageView> 
{
	public:
		static SnPageView* newInstance(Faeris::FsDict* dict);

	public:
		SnPageView();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
		virtual SnAttrGroupList* getAttributeList();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

		bool isDropEnabled();

};



#endif /* _SN_PAGE_VIEW_H_ */
