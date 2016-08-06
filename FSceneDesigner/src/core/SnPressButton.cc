#include "SnPressButton.h"
#include "SnThemeConfig.h"


SnPressButton* SnPressButton::newInstance(Faeris::FsDict* dict)
{
	SnPressButton* ret=new SnPressButton();
	ret->setIdentifyAttributes(dict);
	return ret;
}




SnPressButton::SnPressButton()
{
	setSize(SnThemeConfig::PRESS_BUTTON_DEFAULT_SIZE);
}


int SnPressButton::identifyType()
{
	return SN_CLASS_PRESS_BUTTON;
}

const char *SnPressButton::identifyTypeName()
{
	return "SN_CLASS_PRESS_BUTTON";
}

SnAttrGroupList* SnPressButton::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::PressButton>::getAttributeList();


	SnAttrGroupDesc* group =new SnAttrGroupDesc("PressButton");
	group->addAttrTypeDesc(createAttributeDesc("textureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	glist->addAttrGroupDesc(group);

	return glist;
}


