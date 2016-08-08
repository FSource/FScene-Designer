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
	ret.push_back("mode");
	ret.push_back("pageViews");
	ret.push_back("currentPageIndex");
	return ret;
}




/** attribute For SnPageView Classs **/

void SnPageView_setPages(FsObject* ob,FsArray* attr)
{
	SnPageView* pg_view=dynamic_cast<SnPageView*>(ob);
	int page_nu=attr->size();

	for(int i=0;i<page_nu;i++)
	{

		FsDict* dict=attr->getDict(i);
		if(dict)
		{
			SnIdentify* id=SnGlobal::identifyFactory()->newInstance(dict);
			if(id)
			{
				UiWidget* widget=dynamic_cast<UiWidget*>(id);
				if(widget)
				{
					E_AlignH align_h=E_AlignH::CENTER;
					E_AlignV align_v=E_AlignV::CENTER;

					FsString* st_alh=dict->lookupString("pageAlignH");
					if(st_alh)
					{
						align_h=FsEnum_StrToAlignH(st_alh->cstr());

					}

					FsString* st_alv=dict->lookupString("pageAlignV");
					if(st_alv)
					{
						align_v=FsEnum_StrToAlignV(st_alv->cstr());
					}
					pg_view->addPage(widget,align_h,align_v);
				}
				else 
				{
					FS_TRACE_WARN("Not SubClass Of UiWidget ,Ingore Item(%d)",i);
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

FsArray* SnPageView_getPages(FsObject* ob)
{
	SnPageView* pg_view=dynamic_cast<SnPageView*>(ob);
	int page_nu=pg_view->getPageNu();

	FsArray* ret= FsArray::create();
	for(int i=0;i<page_nu;i++)
	{
		UiWidget* widget=pg_view->getPage(i);
		SnIdentify* id=dynamic_cast<SnIdentify*>(widget);
		FsDict* dict=id->takeObjectFst();
		const char* align_h=FsEnum_AlignHToStr(pg_view->getPageAlignH(i));
		const char* align_v=FsEnum_AlignVToStr(pg_view->getPageAlignV(i));

		dict->insert(FsString::create("pageAlignH"),FsString::create(align_h));
		dict->insert(FsString::create("pageAlignV"),FsString::create(align_v));

		ret->push(dict);

	}
	return ret;

}


SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_SnPageView_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("pageViews",E_FsType::FT_ARRAY,NULL,SnPageView_setPages,SnPageView_getPages),
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnPageView,PageView,0,S_SnPageView_Main_Attr);



