#include "SnEntity2D.h"
#include "stage/layer/FsLayer.h"
#include "stage/entity/FsEntity.h"

int SnEntity2D::identifyType()
{
	return SN_CLASS_ENTITY2D;
}
const char* SnEntity2D::identifyTypeName()
{
	return "SN_CLASS_ENTITY2D";
}


