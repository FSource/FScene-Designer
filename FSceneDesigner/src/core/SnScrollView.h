#ifndef _SN_SCROLL_VIEW_H_
#define _SN_SCROLL_VIEW_H_ 

#include "stage/ui/FsScrollView.h"
#include "SnUiWidget.h"


class SnScrollView:public TSnUiWidget<Faeris::ScrollView>
{
	public:
		FS_CLASS_DECLARE(SnScrollView);
	public:
		static SnScrollView*  newInstance(Faeris::FsDict* dict);
	public:
		SnScrollView();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

		
		virtual SnAttrGroupList* getAttributeList();
		virtual std::vector<std::string> getObjectFstAttrList();

};




#endif /*_SN_SCROLL_VIEW_H_*/

