
#include "stage/entity/FsEntity2D.h"

#include "support/util/FsArray.h"
#include "stage/FsScene.h"

#include "SnClass.h"
#include "SnLayer2D.h"
#include "util/SnUtil.h"
#include "SnGlobal.h"
#include "SnIdentifyFactory.h"
#include "FsClass.h"

NS_FS_USE

SnLayer2D* SnLayer2D::newInstance(Faeris::FsDict* dict)
{
	SnLayer2D* ret=new SnLayer2D();
	ret->setIdentifyAttributes(dict);
	return ret;
}





SnLayer2D::SnLayer2D()
{
	setRefDelete(false);
	m_array=FsArray::create();
	m_array->addRef();
	m_editViewArea.set(0,0,0,0);
	m_className=Layer2D::getClassName();
}

int SnLayer2D::identifyType()
{
	return SN_CLASS_LAYER2D;
}
const char* SnLayer2D::identifyTypeName()
{
	return "SnLayer2D";
}

SnAttrGroupList* SnLayer2D::getAttributeList()
{
	SnAttrGroupList* glist=SnIdentify::getAttributeList();
	SnAttrGroupDesc* group=new SnAttrGroupDesc("Layer2D");

	group->addAttrTypeDesc(createAttributeDesc("visible",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("touchEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("touchesEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("dispatchTouchEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("dispatchTouchesEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("viewArea",SN_TYPE_NORMAL));

	glist->addAttrGroupDesc(group);

	return glist;

}

SnIdentify* SnLayer2D::getIdentifyParent()
{
	Faeris::Scene* sn=getScene();
	SnIdentify* id= dynamic_cast<SnIdentify*>(sn);
	return id;
}

int SnLayer2D::getIdentifyChildNu()
{
	return m_array->size();
}

SnIdentify* SnLayer2D::getIdentifyChild(int index)
{
	Faeris::Entity2D* en=(Entity2D*)m_array->get(index);
	SnIdentify* id=dynamic_cast<SnIdentify*>(en);
	return id;
}

int SnLayer2D::getIdentifyChildIndex(SnIdentify* id)
{
	Entity2D* en=dynamic_cast<Entity2D*>(id);
	int size=m_array->size();
	for(int i=0;i<size;i++)
	{
		if(en==m_array->get(i))
		{
			return i;
		}
	}
	return 0;
}


bool SnLayer2D::isDragEnabled()
{
	return true;
}

bool SnLayer2D::isDropEnabled()
{
	return true;
}


void SnLayer2D::addIdentifyChild(SnIdentify* idenfy)
{
	Entity2D* en=dynamic_cast<Entity2D*>(idenfy);
	Layer2D::add(en);
	m_array->push(en);

}

void SnLayer2D::removeIdentifyChild(SnIdentify* idenfy)
{
	Entity2D* en=dynamic_cast<Entity2D*>(idenfy);
	Layer2D::remove(en);
	m_array->remove(en);


}

void SnLayer2D::clearIdentifyChild()
{
	Layer2D::clearEntity();
	m_array->clear();
}

void SnLayer2D::acceptChild(SnIdentify* id)
{
	Entity2D* en =dynamic_cast<Entity2D*>(id);
	if(en==NULL)
	{
		return false;
	}

	return true;
}



std::vector<SnIdentify*> SnLayer2D::getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse)
{
	std::vector<SnIdentify*> ret;

	int size=m_array->size();
	for(int i=0;i<size;i++)
	{
		Entity2D* en=(Entity2D*)m_array->get(i);
		SnIdentify* id=dynamic_cast<SnIdentify*>(en);
		if(SnUtil::identifyInRect(id,start,end))
		{
			ret.push_back(id);
		}

		if(traverse)
		{
			std::vector<SnIdentify*> r=id->getChildInArea(start,end,traverse);
			ret.insert(ret.end(),r.begin(),r.end());
		}
	}

	return ret;
}
SnIdentify* SnLayer2D::getChildHitPoint(Faeris::Vector2f p,bool traverse)
{

	int size=m_array->size();
	for(int i=size-1;i>=0;i--)
	{
		Entity2D* en=(Entity2D*)m_array->get(i);
		SnIdentify* id=dynamic_cast<SnIdentify*>(en);


		if(traverse)
		{
			SnIdentify* ret= id->getChildHitPoint(p,traverse);
			if(ret)
			{
				return ret;
			}
		}

		if(SnUtil::identifyHitPoint(id,p))
		{
			return id;
		}
	}
	return NULL;

}



std::vector<std::string> SnLayer2D::getObjectFstAttrList()
{
	std::vector<std::string> ret=SnIdentify::getObjectFstAttrList();
	ret.push_back("visible");
	ret.push_back("touchEnabled");
	ret.push_back("touchesEnabled");
	ret.push_back("dispatchTouchEnabled");
	ret.push_back("dispatchTouchesEnabled");
	ret.push_back("viewArea");
	ret.push_back("entity");
	return ret;
}


SnLayer2D::~SnLayer2D()
{
	m_array->decRef();
}


/** Attribute For SnLayer2D  **/


static void SnLayer2D_SetEntity(FsObject* ob,FsArray* attr)
{
	SnLayer2D* ly=dynamic_cast<SnLayer2D*>(ob);
	int entity_nu=attr->size();
	for(int i=0;i<entity_nu;i++)
	{
		FsDict* dict=attr->getDict(i);
		if(dict)
		{
			SnIdentify* id=SnGlobal::identifyFactory()->newInstance(dict);
			if(id)
			{
				Entity2D* en=dynamic_cast<Entity2D*>(id);
				if(en)
				{
					ly->addIdentifyChild(id);
				}
				else 
				{
					FS_TRACE_WARN("Not SubClass Of Entity2D,Ingore Item(%d)",i);
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

static FsArray* SnLayer2D_GetEntity(FsObject* ob)
{
	SnLayer2D* ly=dynamic_cast<SnLayer2D*>(ob);

	FsArray* ret= FsArray::create();

	int layer_nu=ly->getIdentifyChildNu();

	for(int i=0;i<layer_nu;i++)
	{
		SnIdentify* id=ly->getIdentifyChild(i);
		FsDict* dict=id->takeObjectFst();
		ret->push(dict);
	}

	return ret;
}


SN_CLASS_ATTR_SET_GET_FUNCTION(SnLayer2D,setEditViewArea,getEditViewArea,Rect2D);

SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);
SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);

static FsClass::FsAttributeDeclare S_SnLayer2D_Main_Attr[]={

	FS_CLASS_ATTR_DECLARE("entity",E_FsType::FT_ARRAY,NULL,SnLayer2D_SetEntity,SnLayer2D_GetEntity),
	FS_CLASS_ATTR_DECLARE("viewArea",E_FsType::FT_F_RECT2D,NULL,SnLayer2D_setEditViewArea,SnLayer2D_getEditViewArea),
	
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),

	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};

FS_CLASS_IMPLEMENT_WITH_BASE(SnLayer2D,Layer2D,0,S_SnLayer2D_Main_Attr);



