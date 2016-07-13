#include "SnMsgCenter.h"

SnMsgCenter::SnMsgCenter()
{
}

SnMsgCenter::~SnMsgCenter()
{
}


/* project */
void SnMsgCenter::emitCurProjectChange()
{
	emit signalCurProjectChange();
}

void SnMsgCenter::emitCurSceneChange()
{
	emit signalCurSceneChange();
}

void SnMsgCenter::emitLayer2DAdd(SnLayer2D* ly)
{
	emit signalLayer2DAdd(ly);
}

void SnMsgCenter::emitCurLayerChange(SnLayer2D* ly)
{
	emit signalCurLayerChange(ly);
}
void SnMsgCenter::emitCurEntityChange()
{
	emit signalCurEntityChange();
}
















