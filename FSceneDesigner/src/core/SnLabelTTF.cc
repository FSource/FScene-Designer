#include "SnLabelTTF.h"

#include "SnClass.h"
#include "FsClass.h"
#include "FsEnums.h"
NS_FS_USE

SnLabelTTF* SnLabelTTF::newInstance(Faeris::FsDict* dict)
{
	SnLabelTTF* ret =new SnLabelTTF();
	ret->setIdentifyAttributes(dict);
	return ret;
}

SnLabelTTF::SnLabelTTF()
{
	init();
	setString("LabelTTF");
	
}


int SnLabelTTF::identifyType()
{
	return SN_CLASS_LABEL_TTF;
}

const char *SnLabelTTF::identifyTypeName()
{
	return "SnLabelTTF";
}


std::vector<std::string> SnLabelTTF::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnEntity2D<Faeris::LabelTTF>::getObjectFstAttrList();

	ret.push_back("fontName");
	ret.push_back("fontSize");
	ret.push_back("textAlign");
	ret.push_back("lineGap");
	ret.push_back("boundSize");
	ret.push_back("string");
	ret.push_back("children");

	return ret;
}



SnAttrGroupList* SnLabelTTF::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::LabelTTF>::getAttributeList();
	SnAttrGroupDesc* group =new SnAttrGroupDesc("LabelTTF");
	group->addAttrTypeDesc(createAttributeDesc("string",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("fontName",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("fontSize",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("textAlign",Faeris::FsEnum_TextAlignGetEnumName));
	group->addAttrTypeDesc(createAttributeDesc("lineGap",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("boundSize",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);

	return glist;
}



SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);


static FsClass::FsAttributeDeclare S_LabelTTF_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("children",E_FsType::FT_ARRAY,NULL,TSnEntity2D_setChildren,TSnEntity2D_getChildren),
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};

FS_CLASS_IMPLEMENT_WITH_BASE(SnLabelTTF,LabelTTF,0,S_LabelTTF_Main_Attr);




