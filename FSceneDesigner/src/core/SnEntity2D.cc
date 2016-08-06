#include "SnEntity2D.h"
#include "stage/layer/FsLayer.h"
#include "stage/entity/FsEntity.h"


SnEntity2D* SnEntity2D::newInstance(Faeris::FsDict* dict)
{
	SnEntity2D* ret=new SnEntity2D();
	ret->setIdentifyAttributes(dict);
	return ret;
}



int SnEntity2D::identifyType()
{
	return SN_CLASS_ENTITY2D;
}

const char* SnEntity2D::identifyTypeName()
{
	return "SN_CLASS_ENTITY2D";
}

