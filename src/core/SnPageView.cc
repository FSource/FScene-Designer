#include "SnPageView.h"


SnPageView* SnPageView::newInstance(Faeris::FsDict* dict)
{
	SnPageView* ret=new SnPageView();
	ret->setIdentifyAttributes(dict);
	return ret;
}






SnPageView::SnPageView ()
{
	setSize(64,64);
	setBgEnabled(true);
	setBgColor(Faeris::Color(255,255,255,200));
	setMode(Faeris::E_ScrollDirection::HORIZONTAL);
}

int SnPageView::identifyType()
{
	return SN_CLASS_PAGE_VIEW;
}
const char* SnPageView::identifyTypeName()
{
	return "SN_CLASS_PAGE_VIEW";
}


SnIdentify* SnPageView::getIdentifyParent()
{
	UiWidget* widget=getParentWidget();
	if(widget!=NULL)
	{
		return dynamic_cast<SnIdentify*>(widget);
	}

	return TSnEntity2D<PageView>::getIdentifyParent();
}

int SnPageView::getIdentifyChildNu()
{
	if(getCurrentPage()==NULL)
	{
		return 0;
	}

	return 1;
}


SnIdentify* SnPageView::getIdentifyChild(int index)
{
	if (index!=0)
	{
		return NULL;
	}

	UiWidget* widget=getCurrentPage();

	return dynamic_cast<SnIdentify*>(widget);
}

int SnPageView::getIdentifyChildIndex(SnIdentify* id)
{
	return 0;
}


bool SnPageView::isDropEnabled()
{
	return false;
}


SnAttrGroupList* SnPageView::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::PageView>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("UiWidget");

	group->addAttrTypeDesc(createAttributeDesc("scissorEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgTextureUrl",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgColor",SN_TYPE_NORMAL));

	glist->addAttrGroupDesc(group);
	group =new SnAttrGroupDesc("PageView");
	group->addAttrTypeDesc(createAttributeDesc("mode",Faeris::FsEnum_ScrollDirectionGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("currentPageIndex",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("currentPageAlignH",Faeris::FsEnum_AlignHGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("currentPageAlignV",Faeris::FsEnum_AlignVGetEnumName));

	glist->addAttrGroupDesc(group);
	return glist;

}

