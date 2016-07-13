#include "core/SnIdentify.h"

NS_FS_USE
SnIdentify::SnIdentify()
{
}
SnIdentify::~SnIdentify()
{
}

int SnIdentify::identifyType()
{
	return SN_CLASS_IDENTIFY;
}
const char* SnIdentify::identifyTypeName()
{
	return "SnIdentify";
}

SnIdentify* SnIdentify::getIdentifyParent(){return NULL;}
int SnIdentify::getIdentifyChildNu( ){return 0;}
SnIdentify* SnIdentify:: getIdentifyChild(int ){return NULL;}
int SnIdentify::getIdentifyChildIndex(SnIdentify* ){return -1;}


bool SnIdentify::isDragEnabled(){return false;}
bool SnIdentify::isDropEnabled(){return false;}



SnAttrGroupList* SnIdentify::getAttributeList()
{
	SnAttrGroupDesc* group=new SnAttrGroupDesc("FsObject");

	group->addAttrTypeDesc(createAttributeDesc("className",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("objectName",SN_TYPE_NORMAL));

	SnAttrGroupList* g_list=new SnAttrGroupList;
	g_list->addAttrGroupDesc(group);

	return g_list;
}


void SnIdentify::setAttribute(const char* name,const FsVariant&  value)
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	ob->setAttribute(name,value);
}

FsVariant SnIdentify::getAttribute(const char* name)
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	FsVariant ret= ob->getAttribute(name);
	return ret;
}

void SnIdentify::setIdentifyName(const char* name)
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	ob->setObjectName(name);
}

const char* SnIdentify::getIdentifyName()
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	return ob->getObjectName();
}




SnAttrTypeDesc* SnIdentify::createAttributeDesc(const char* name,int type)
{
	return new SnAttrTypeDesc(name,type);
}

SnAttrTypeDesc* SnIdentify::createAttributeDesc(const char* name,const char* fn(int))
{
	QStringList e_list;
	int index=0;
	while(fn(index)!=NULL)
	{
		e_list<<fn(index);
		index++;
	}
	return new SnAttrTypeDesc(name,e_list);
}

