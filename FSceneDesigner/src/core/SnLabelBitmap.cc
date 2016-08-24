#include "SnLabelBitmap.h"

#include "SnClass.h"
#include "FsClass.h"
#include "FsEnums.h"
NS_FS_USE

SnLabelBitmap* SnLabelBitmap::newInstance(Faeris::FsDict* dict)
{
	SnLabelBitmap* ret=new SnLabelBitmap();
	ret->setIdentifyAttributes(dict);
	return ret;
}

SnLabelBitmap::SnLabelBitmap()
{
	setString("LabelBitmap");
}

int SnLabelBitmap::identifyType()
{
	return SN_CLASS_LABEL_BMP;
}

const char* SnLabelBitmap::identifyTypeName()
{
	return "SnLabelBitmap";
}


std::vector<std::string> SnLabelBitmap::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnEntity2D<Faeris::LabelBitmap>::getObjectFstAttrList();

	ret.push_back("fontName");
	ret.push_back("fontSize");
	ret.push_back("textAlign");
	ret.push_back("lineGap");
	ret.push_back("boundSize");
	ret.push_back("string");
	ret.push_back("children");

	return ret;
}


SnAttrGroupList* SnLabelBitmap::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::LabelBitmap>::getAttributeList();
	SnAttrGroupDesc* group =new SnAttrGroupDesc("LabelBitmap");
	group->addAttrTypeDesc(createAttributeDesc("string",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("fontName",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("fontSize",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("textAlign",Faeris::FsEnum_TextAlignGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("lineGap",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("boundSize",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;
}


SN_CLASS_ATTR_SET_GET_FUNCTION(SnIdentify,setExport,getExport,bool);
SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);


static FsClass::FsAttributeDeclare S_LabelBitmap_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("export",E_FsType::FT_B_1,NULL,SnIdentify_setExport,SnIdentify_getExport),

	FS_CLASS_ATTR_DECLARE("children",E_FsType::FT_ARRAY,NULL,TSnEntity2D_setChildren,TSnEntity2D_getChildren),
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};

FS_CLASS_IMPLEMENT_WITH_BASE(SnLabelBitmap,LabelBitmap,0,S_LabelBitmap_Main_Attr);


