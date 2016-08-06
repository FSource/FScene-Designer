#include "SnLabelTTF.h"


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
	return "SN_CLASS_LABEL_TTF";
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
