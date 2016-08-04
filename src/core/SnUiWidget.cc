#include "SnUiWidget.h"


SnUiWidget* SnUiWidget::newInstance(Faeris::FsDict* dict)
{
	SnUiWidget* ret=new SnUiWidget();
	ret->setIdentifyAttributes(dict);
	return ret;
}


SnUiWidget::SnUiWidget()
{
	setSize(64,64);
	setBgEnabled(true);
	setBgColor(Faeris::Color(255,255,255,200));
}

int SnUiWidget::identifyType()
{
	return SN_CLASS_UI_WIDGET;
}
const char* SnUiWidget::identifyTypeName()
{
	return "SN_CLASS_UI_WIDGET";
}

SnIdentify* SnUiWidget::getIdentifyParent()
{
	UiWidget* widget=getParentWidget();
	if(widget!=NULL)
	{
		return dynamic_cast<SnIdentify*>(widget);
	}

	return TSnEntity2D<UiWidget>::getIdentifyParent();
}

SnAttrGroupList* SnUiWidget::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::UiWidget>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("UiWidget");

	group->addAttrTypeDesc(createAttributeDesc("scissorEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgTextureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	group->addAttrTypeDesc(createAttributeDesc("bgColor",SN_TYPE_NORMAL));

	glist->addAttrGroupDesc(group);
	return glist;

}

