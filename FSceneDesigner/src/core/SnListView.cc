#include "SnListView.h"
#include "SnClass.h"
#include "FsClass.h"
#include "FsEnums.h"


NS_FS_USE
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
	return "SnListView";
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
	SnAttrGroupList* glist=TSnUiWidget<Faeris::ListView>::getAttributeList();

	SnAttrGroupDesc* group=new SnAttrGroupDesc("ScrollView");
	group->addAttrTypeDesc(createAttributeDesc("scrollY",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("scrollX",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	group =new SnAttrGroupDesc("ListView");
	group->addAttrTypeDesc(createAttributeDesc("mode",Faeris::FsEnum_ScrollDirectionGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("listGap",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;
}

std::vector<std::string> SnListView::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnUiWidget<ListView>::getObjectFstAttrList();
	ret.push_back("scrollX");
	ret.push_back("scrollY");
	ret.push_back("mode");
	ret.push_back("listGap");
	return ret;
}



/* class attribute */

SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_SnListView_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),

	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnListView,ListView,0,S_SnListView_Main_Attr);











