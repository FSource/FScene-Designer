#include "SnQuad2D.h"
#include "FsClass.h"
#include "SnClass.h"

NS_FS_USE

SnQuad2D* SnQuad2D::newInstance(Faeris::FsDict* dict)
{
	SnQuad2D* ret=new SnQuad2D();
	ret->setIdentifyAttributes(dict);
	return ret;
}


SnQuad2D::SnQuad2D()
{
	setSize(64,64);
}
int SnQuad2D::identifyType()
{
	return SN_CLASS_QUAD2D;
}

const char* SnQuad2D::identifyTypeName()
{
	return "SnQuad2D";
}


SnAttrGroupList* SnQuad2D::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::Quad2D>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("Quad2D");
	group->addAttrTypeDesc(createAttributeDesc("resourceUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));

	glist->addAttrGroupDesc(group);
	return glist;

}



std::vector<std::string> SnQuad2D::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnEntity2D<Faeris::Quad2D>::getObjectFstAttrList();
	ret.push_back("resourceUrl");
	ret.push_back("size");
	ret.push_back("children");

	return ret;
}


SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_Quad2D_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("children",E_FsType::FT_ARRAY,NULL,TSnEntity2D_setChildren,TSnEntity2D_getChildren),
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};

FS_CLASS_IMPLEMENT_WITH_BASE(SnQuad2D,Quad2D,0,S_Quad2D_Main_Attr);



