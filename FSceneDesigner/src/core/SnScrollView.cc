#include "SnScrollView.h"
#include "SnClass.h"
#include "FsClass.h"


#include "FsEnums.h"

NS_FS_USE

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
	return "SnScrollView";
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
	SnAttrGroupList* glist=TSnUiWidget<Faeris::ScrollView>::getAttributeList();


	SnAttrGroupDesc* group=new SnAttrGroupDesc("ScrollView");

	group->addAttrTypeDesc(createAttributeDesc("scrollX",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("scrollY",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;

}

std::vector<std::string> SnScrollView::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnUiWidget<ScrollView>::getObjectFstAttrList();
	ret.push_back("scrollX");
	ret.push_back("scrollY");
	return ret;
}




/* class attribute */

SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);




static FsClass::FsAttributeDeclare S_SnScrollView_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnScrollView,ScrollView,0,S_SnScrollView_Main_Attr);



