#ifndef _SN_PRESS_BUTTON_H_
#define _SN_PRESS_BUTTON_H_ 

#include "stage/ui/FsPressButton.h"
#include "SnTEntity2D.h"


class SnPressButton:public TSnEntity2D<Faeris::PressButton> 
{
	public:
		static SnPressButton* newInstance(Faeris::FsDict* dict);

	public:
		SnPressButton();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
		virtual SnAttrGroupList* getAttributeList();
};


#endif /*_SN_PRESS_BUTTON_H_*/

