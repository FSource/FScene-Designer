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
















