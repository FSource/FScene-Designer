#ifndef _SN_LIST_VIEW_H_
#define _SN_LIST_VIEW_H_ 

#include "stage/ui/FsListView.h"
#include "SnTEntity2D.h"


class SnListView:public TSnEntity2D<Faeris::ListView>
{
	public:
		static SnListView* newInstance(Faeris::FsDict* dict);

	public:
		SnListView();

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





#endif /*_SN_LIST_VIEW_H_*/

