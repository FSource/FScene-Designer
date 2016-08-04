#include "SnScrollView.h"

SnScrollView* SnScrollView::newInstance(Faeris::FsDict* dict)
{
	SnScrollView* ret=new SnScrollView();
	ret->setIdentifyAttributes(dict);
	return ret;
}


SnScrollView::SnScrollView()
{
	setSize(64,64);
	setBgEnabled(true);
	setBgColor(Faeris::Color(255,255,255,200));
}

int SnScrollView::identifyType()
{
	return SN_CLASS_SCROLL_VIEW;
}

const char* SnScrollView::identifyTypeName()
{
	return "SN_CLASS_SCROLL_VIEW";
}

SnIdentify* SnScrollView::getIdentifyParent()
{
	UiWidget* widget=getParentWidget();
	if(widget!=NULL)
	{
		return dynamic_cast<SnIdentify*>(widget);
	}
	return TSnEntity2D<ScrollView>::getIdentifyParent();
}

int SnScrollView::getIdentifyChildNu()
{
	if(getContentWidget()==NULL)
	{
		return 0;
	}
	return 1;
}

SnIdentify* SnScrollView::getIdentifyChild(int index)
{
	UiWidget* widget=getContentWidget();
	return dynamic_cast<SnIdentify*>(widget);
}

int SnScrollView::getIdentifyChildIndex(SnIdentify* id)
{
	return 0;
}






SnAttrGroupList* SnScrollView::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::ScrollView>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("UiWidget");
	group->addAttrTypeDesc(createAttributeDesc("scissorEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgTextureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	group->addAttrTypeDesc(createAttributeDesc("bgColor",SN_TYPE_NORMAL));

	glist->addAttrGroupDesc(group);

	group=new SnAttrGroupDesc("ScrollView");

	group->addAttrTypeDesc(createAttributeDesc("scrollX",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("scrollY",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;

}





