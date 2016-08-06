#include "SnPageView.h"
#include "SnClass.h"
#include "FsClass.h"
#include "FsEnums.h"

NS_FS_USE


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
	return "SnPageView";
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
	SnAttrGroupList* glist=TSnUiWidget<Faeris::PageView>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("PageView");
	group->addAttrTypeDesc(createAttributeDesc("mode",Faeris::FsEnum_ScrollDirectionGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("currentPageIndex",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("currentPageAlignH",Faeris::FsEnum_AlignHGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("currentPageAlignV",Faeris::FsEnum_AlignVGetEnumName));

	glist->addAttrGroupDesc(group);
	return glist;

}



std::vector<std::string> SnPageView::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnUiWidget<PageView>::getObjectFstAttrList();
	ret.push_back("currentPageIndex");
	return ret;
}




SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_SnPageView_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnPageView,PageView,0,S_SnPageView_Main_Attr);



