#include "SnScene.h"

#include "stage/layer//FsLayer.h"


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




SnAttrGroupList* SnScene::getAttributeList()
{
	SnAttrGroupList* glist=SnIdentify::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("Scene");
	group->addAttrTypeDesc(createAttributeDesc("touchEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("touchesEnabled",SN_TYPE_NORMAL));
	glist->addAttrGroupDesc(group);
	return glist;

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
	int size=layerNu();

	Faeris::Layer* layer=getLayer(size-1-index);

	SnIdentify* id=dynamic_cast<SnIdentify*>(layer);
	return id;
}


