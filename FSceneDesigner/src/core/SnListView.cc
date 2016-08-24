#include "SnListView.h"
#include "SnClass.h"
#include "FsClass.h"
#include "FsEnums.h"
#include "SnGlobal.h"
#include "SnIdentifyFactory.h"


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

void SnListView::addIdentifyChild(SnIdentify* id)
{
	UiWidget* widget=dynamic_cast<UiWidget*>(id);
	assert(widget);
	addListItem(widget);
}

void SnListView::removeIdentifyChild(SnIdentify* id)
{
	UiWidget* widget=dynamic_cast<UiWidget*>(id);
	assert(widget);
	removeListItem(widget);
}

void SnListView::clearIdentifyChild()
{
	clearListItem();
}

bool SnListView::acceptChild(SnIdentify* id)
{
	UiWidget* en =dynamic_cast<UiWidget*>(id);
	if(en==NULL)
	{
		return false;
	}

	return true;
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
	ret.push_back("mode");
	ret.push_back("listGap");
	ret.push_back("listItems");

	ret.push_back("scrollX");
	ret.push_back("scrollY");

	return ret;
}



/* class attribute */
static void SnListView_setListItem(FsObject* ob,FsArray* attr)
{
	SnListView* view=dynamic_cast<SnListView*>(ob);

	int item_nu=attr->size();
	for(int i=0;i<item_nu;i++)
	{
		FsDict* dict=attr->getDict(i);
		if(dict)
		{
			SnIdentify* id=SnGlobal::identifyFactory()->newInstance(dict);
			if(id)
			{
				UiWidget* en=dynamic_cast<UiWidget*>(id);
				if(en)
				{
					view->addIdentifyChild(id);
				}
				else 
				{
					FS_TRACE_WARN("Not SubClass Of UiWidget,Ingore Item(%d)",i);
					delete id;
				}
			}
		}
		else 
		{
			FS_TRACE_WARN("Not Dict,Ingore Item(%d)",i);
		}
	}
}

static FsArray* SnListView_getListItem(FsObject* ob)
{

	SnListView* view=dynamic_cast<SnListView*>(ob);
	unsigned int flags=view->getSaveAndExportFlags();
	FsArray* ret=FsArray::create();

	int item_nu=view->getIdentifyChildNu();

	for(int i=0;i<item_nu;i++)
	{

		SnIdentify* id=view->getIdentifyChild(i);
		if(flags&IGNORE_EXPORT)
		{
			if(!id->getExport())
			{
				continue;
			}
		}

		FsDict* dict=id->takeObjectFst(flags);
		ret->push(dict);
	}
	return ret;
}





SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);
SN_CLASS_ATTR_SET_GET_FUNCTION(SnIdentify,setExport,getExport,bool);


static FsClass::FsAttributeDeclare S_SnListView_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("export",E_FsType::FT_B_1,NULL,SnIdentify_setExport,SnIdentify_getExport),
	FS_CLASS_ATTR_DECLARE("listItems",E_FsType::FT_ARRAY,NULL,SnListView_setListItem,SnListView_getListItem),

	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnListView,ListView,0,S_SnListView_Main_Attr);











