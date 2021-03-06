#include "SnUiWidget.h"

#include "SnClass.h"
#include "FsClass.h"
#include "FsEnums.h"

NS_FS_USE

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
	return "SnUiWidget";
}


std::vector<std::string> SnUiWidget::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnUiWidget<Faeris::UiWidget>::getObjectFstAttrList();
	ret.push_back("children");
	return ret;
}



/* class attribute */

SN_CLASS_ATTR_SET_GET_FUNCTION(SnIdentify,setExport,getExport,bool);
SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_SnUiWidget_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("children",E_FsType::FT_ARRAY,NULL,TSnEntity2D_setChildren,TSnEntity2D_getChildren),
	FS_CLASS_ATTR_DECLARE("export",E_FsType::FT_B_1,NULL,SnIdentify_setExport,SnIdentify_getExport),
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnUiWidget,UiWidget,0,S_SnUiWidget_Main_Attr);
