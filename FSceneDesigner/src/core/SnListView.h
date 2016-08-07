#ifndef _SN_LIST_VIEW_H_
#define _SN_LIST_VIEW_H_ 

#include "stage/ui/FsListView.h"
#include "SnTUiWidget.h"


class SnListView:public TSnUiWidget<Faeris::ListView>
{
	public:
		FS_CLASS_DECLARE(SnListView);

	public:
		static SnListView* newInstance(Faeris::FsDict* dict);

	public:
		SnListView();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

		virtual void addIdentifyChild(SnIdentify* idenfy);
		virtual void removeIdentifyChild(SnIdentify* idenfy);
		virtual void clearIdentifyChild();


		virtual SnAttrGroupList* getAttributeList();
		virtual std::vector<std::string> getObjectFstAttrList();

		bool isDropEnabled();

};





#endif /*_SN_LIST_VIEW_H_*/

