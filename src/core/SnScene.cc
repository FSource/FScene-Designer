#include "SnScene.h"

#include "stage/layer//FsLayer.h"

int SnScene::identifyType()
{
	return SN_CLASS_SCENE;
}
const char* SnScene::identifyTypeName()
{
	return "SnScene";
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
int SnScene::getIdentifyChildIndex(SnIdentify* id)
{
	return 0;
}