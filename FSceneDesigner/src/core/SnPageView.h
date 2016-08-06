#ifndef _SN_PAGE_VIEW_H_
#define _SN_PAGE_VIEW_H_ 

#include "stage/ui/FsPageView.h"
#include "SnTUiWidget.h"

class SnPageView:public TSnUiWidget<Faeris::PageView> 
{
	public:
		FS_CLASS_DECLARE(SnPageView);

	public:
		static SnPageView* newInstance(Faeris::FsDict* dict);

	public:
		SnPageView();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

	

		virtual SnAttrGroupList* getAttributeList();
		virtual std::vector<std::string> getObjectFstAttrList();
		
		bool isDropEnabled();

};



#endif /* _SN_PAGE_VIEW_H_ */
