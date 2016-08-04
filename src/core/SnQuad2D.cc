#include "SnQuad2D.h"

SnQuad2D* SnQuad2D::newInstance(Faeris::FsDict* dict)
{
	SnQuad2D* ret=new SnQuad2D();
	ret->setIdentifyAttributes(dict);
	return ret;
}


int SnQuad2D::identifyType()
{
	return SN_CLASS_QUAD2D;
}

const char* SnQuad2D::identifyTypeName()
{
	return "SN_CLASS_QUAD2D";
}


SnAttrGroupList* SnQuad2D::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<Faeris::Quad2D>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("Quad2D");
	group->addAttrTypeDesc(createAttributeDesc("resourceUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));

	glist->addAttrGroupDesc(group);
	return glist;

}



char** SnQuad2D::getObjectFstAttrList()
{
	static char* attrs[]={
		"resourceUrl",
		"position",
		"scale",
		"rotateZ",
		"visible",
		"visibles",
		"anchor",
		"size",
		"touchEnabled",
		"touchesEnabled",
		"touchDispatchEnabled",
		"touchesDispatchEnabled",
		"color",
		"opacity",
		"blendEquation",
		"blendSrc",
		"blendDst",
		NULL,
	}; 

	return attrs;
}
