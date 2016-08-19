#include "SnPressButton.h"
#include "SnThemeConfig.h"
#include "FsClass.h"
#include "SnClass.h"

NS_FS_USE
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
	return "SnPressButton";
}


std::vector<std::string> SnPressButton::getObjectFstAttrList()
{
	std::vector<std::string> ret= TSnEntity2D<Faeris::PressButton>::getObjectFstAttrList();
	ret.push_back("textureUrl");
	ret.push_back("tweenColorEnabled");
	ret.push_back("tweenTextureEnabled");
	ret.push_back("tweenScaleEnabled");
	ret.push_back("tweenSizeEnabled");

	ret.push_back("normalState");
	ret.push_back("pressState");
	ret.push_back("disableState");

	return ret;
}
SnAttrGroupList* SnPressButton::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::PressButton>::getAttributeList();


	SnAttrGroupDesc* group =new SnAttrGroupDesc("PressButton");
	group->addAttrTypeDesc(createAttributeDesc("textureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	glist->addAttrGroupDesc(group);

	group=new SnAttrGroupDesc("TweenFlags");
	group->addAttrTypeDesc(createAttributeDesc("tweenColorEnabled","color",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("tweenTextureEnabled","texture",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("tweenScaleEnabled","scale",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	group=new SnAttrGroupDesc("NormalState");
	group->addAttrTypeDesc(createAttributeDesc("normalState.textureUrl","textureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	group->addAttrTypeDesc(createAttributeDesc("normalState.color","color",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("normalState.scale","scale",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	group=new SnAttrGroupDesc("PressState");
	group->addAttrTypeDesc(createAttributeDesc("pressState.textureUrl","textureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	group->addAttrTypeDesc(createAttributeDesc("pressState.color","color",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("pressState.scale","scale",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);



	group=new SnAttrGroupDesc("DisableState");
	group->addAttrTypeDesc(createAttributeDesc("disableState.textureUrl","textureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	group->addAttrTypeDesc(createAttributeDesc("disableState.color","color",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("disableState.scale","scale",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;
}


SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_SnPressButton_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),

	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};
FS_CLASS_IMPLEMENT_WITH_BASE(SnPressButton,PressButton,0,S_SnPressButton_Main_Attr);

