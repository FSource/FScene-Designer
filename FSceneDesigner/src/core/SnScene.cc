#include "SnScene.h"

#include "FsClass.h"
#include "SnClass.h"
#include "stage/layer//FsLayer.h"
#include "FsObject.h"
#include "SnGlobal.h"
#include "SnIdentifyFactory.h"
#include "SnLayer2D.h"


NS_FS_USE

SnScene* SnScene::newInstance(Faeris::FsDict* dict)
{
	SnScene* ret=new SnScene();
	ret->setIdentifyAttributes(dict);
	return ret;
}


int SnScene::identifyType()
{
	return SN_CLASS_SCENE;
}




const char* SnScene::identifyTypeName()
{
	return "SnScene";
}


SnScene::SnScene()
{
	setRefDelete(false);
	m_className=Scene::getClassName();
}

SnAttrGroupList* SnScene::getAttributeList()
{
	SnAttrGroupList* glist=SnIdentify::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("Scene");
	group->addAttrTypeDesc(createAttributeDesc("touchEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("touchesEnabled",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);
	return glist;

}

std::vector<std::string> SnScene::getObjectFstAttrList()
{
	std::vector<std::string> ret=SnIdentify::getObjectFstAttrList();
	ret.push_back("touchEnabled");
	ret.push_back("touchesEnabled");
	ret.push_back("layers");

	return ret;
}

SnIdentify* SnScene::getIdentifyParent()
{
	return NULL;
}



int SnScene::getIdentifyChildNu()
{
	return layerNu();
}

SnIdentify* SnScene::getIdentifyChild(int index)
{

	Faeris::Layer* layer=getLayer(index);

	SnIdentify* id=dynamic_cast<SnIdentify*>(layer);
	return id;
}

void SnScene::addIdentifyChild(SnIdentify* id)
{
	SnLayer2D* ly=dynamic_cast<SnLayer2D*>(id);
	push(ly);

}

void SnScene::removeIdentifyChild(SnIdentify* id)
{
	SnLayer2D* ly=dynamic_cast<SnLayer2D*>(id);
	remove(ly);
}

void SnScene::clearIdentifyChild()
{
	clear();
}



/** user For SnScene Attribute **/


static void SnScene_SetLayers(FsObject* ob,FsArray* attr)
{
	SnScene* sn=dynamic_cast<SnScene*>(ob);

	int child_nu=attr->size();

	for(int i=0;i<child_nu;i++)
	{
		FsDict* dict=attr->getDict(i);
		if(dict)
		{
			SnIdentify* id=SnGlobal::identifyFactory()->newInstance(dict);

			if(id)
			{
				SnLayer2D* ly=dynamic_cast<SnLayer2D*>(id);
				if(ly)
				{
					sn->addIdentifyChild(ly);
				}
				else 
				{
					FS_TRACE_WARN("Not SubClass Of Layer,Ingore Item(%d)",i);
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

static FsArray* SnScene_GetLayers(FsObject* ob)
{
	SnScene* sn=dynamic_cast<SnScene*>(ob);

	FsArray* ret= FsArray::create();

	int layer_nu=sn->getIdentifyChildNu();

	for(int i=0;i<layer_nu;i++)
	{
		SnIdentify* id=sn->getIdentifyChild(i);
		FsDict* dict=id->takeObjectFst();
		ret->push(dict);
	}

	return ret;
}



/* class attribute */

SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(SnIdentify,setIdentifyClassName,getIdentifyClassName);

SN_CLASS_ATTR_GET_CHARS_FUNCTION(SnIdentify,identifyTypeName);


static FsClass::FsAttributeDeclare S_SnScene_Main_Attr[]={
	FS_CLASS_ATTR_DECLARE("layers",E_FsType::FT_ARRAY,NULL,SnScene_SetLayers,SnScene_GetLayers),
	FS_CLASS_ATTR_DECLARE("className",E_FsType::FT_CHARS,NULL,SnIdentify_setIdentifyClassName,SnIdentify_getIdentifyClassName),
	FS_CLASS_ATTR_DECLARE("editClass",E_FsType::FT_CHARS,NULL,0,SnIdentify_identifyTypeName),
	
	FS_CLASS_ATTR_DECLARE(NULL,E_FsType::FT_IN_VALID,NULL,0,0)
};


FS_CLASS_IMPLEMENT_WITH_BASE(SnScene,Scene,0,S_SnScene_Main_Attr);







