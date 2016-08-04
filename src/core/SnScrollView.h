#ifndef _SN_SCROLL_VIEW_H_
#define _SN_SCROLL_VIEW_H_ 

#include "stage/ui/FsScrollView.h"
#include "SnTEntity2D.h"


class SnScrollView:public TSnEntity2D<Faeris::ScrollView>
{
	public:
		static SnScrollView*  newInstance(Faeris::FsDict* dict);
	public:
		SnScrollView();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
		virtual SnAttrGroupList* getAttributeList();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

};




#endif /*_SN_SCROLL_VIEW_H_*/

