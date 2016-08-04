#include "SnListView.h"


SnListView* SnListView::newInstance(Faeris::FsDict* dict)
{
	SnListView* ret=new SnListView();
	ret->setIdentifyAttributes(dict);
	return ret;
}

SnListView::SnListView()
{
	setSize(64,128);
	setBgEnabled(true);
	setBgColor(Faeris::Color(255,255,255,200));
	setMode(Faeris::E_ScrollDirection::VERTICAL);
}

int SnListView::identifyType()
{
	return SN_CLASS_LIST_VIEW;
}

const char* SnListView::identifyTypeName()
{
	return "SN_CLASS_LIST_VIEW";
}


SnIdentify* SnListView::getIdentifyParent()
{
	UiWidget* widget=getParentWidget();
	if(widget!=NULL)
	{
		return dynamic_cast<SnIdentify*>(widget);
	}

	return TSnEntity2D<ListView>::getIdentifyParent();
}



int SnListView::getIdentifyChildNu()
{
	return getListItemNu();
}



SnIdentify* SnListView::getIdentifyChild(int index)
{
	UiWidget* widget=getListItem(index);
	return dynamic_cast<SnIdentify*>(widget);
}

int SnListView::getIdentifyChildIndex(SnIdentify* id)
{
	UiWidget* widget=dynamic_cast<UiWidget*>(id);

	return getListItemIndex(widget);
}



bool SnListView::isDropEnabled()
{
	return false;
}

SnAttrGroupList* SnListView::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::ListView>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("UiWidget");

	group->addAttrTypeDesc(createAttributeDesc("scissorEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgTextureUrl",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgColor",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	group=new SnAttrGroupDesc("ScrollView");
	group->addAttrTypeDesc(createAttributeDesc("scrollY",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("scrollX",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	group =new SnAttrGroupDesc("ListView");
	group->addAttrTypeDesc(createAttributeDesc("mode",Faeris::FsEnum_ScrollDirectionGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("listGap",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;

}













