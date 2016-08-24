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

bool SnQuad2D::filterExportValue(const char* name,const FsVariant& vs)
{
	if(strcmp(name,"resourceUrl")==0)
	{
		if(vs.getType()==Faeris::E_FsType::FT_CHARS)
		{
			const char* value=(char*)vs.getValue();
			if(strcmp(value,"")==0)
			{
				return true;
			}
		}
	}
	return  TSnEntity2D<Quad2D>::filterExportValue(name,vs);
}



SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);
SN_CLASS_ATTR_SET_GET_FUNCTION(SnIdentify,setExport,getExport,bool);

static FsClass::FsAttributeDeclare S_Quad2D_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	FS_CLASS_ATTR_DECLARE("children",E_FsType::FT_ARRAY,NULL,TSnEntity2D_setChildren,TSnEntity2D_getChildren),
	FS_CLASS_ATTR_DECLARE("export",E_FsType::FT_B_1,NULL,SnIdentify_setExport,SnIdentify_getExport),
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};

FS_CLASS_IMPLEMENT_WITH_BASE(SnQuad2D,Quad2D,0,S_Quad2D_Main_Attr);



