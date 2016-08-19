#ifndef _SN_PRESS_BUTTON_H_
#define _SN_PRESS_BUTTON_H_ 

#include "stage/ui/FsPressButton.h"
#include "SnTEntity2D.h"


class SnPressButton:public TSnEntity2D<Faeris::PressButton> 
{
	public:
		FS_CLASS_DECLARE(SnPressButton);

	public:
		static SnPressButton* newInstance(Faeris::FsDict* dict);

	public:
		SnPressButton();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
		virtual SnAttrGroupList* getAttributeList();
		virtual std::vector<std::string> getObjectFstAttrList();
};


#endif /*_SN_PRESS_BUTTON_H_*/

