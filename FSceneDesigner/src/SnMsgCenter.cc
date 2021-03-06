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



void SnMsgCenter::emitIdentifyAttributeChange(SnIdentify* id,const char* name)
{
	emit signalIdentifyAttributeChange(id, name);
}

void SnMsgCenter::emitCurrrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st)
{
	emit signalCurrentAndSelectsChange(id,st);

}


void SnMsgCenter::emitEditModeChange(SN_EditMode mode)
{
	emit signalEditModeChange(mode);
}

void SnMsgCenter::emitTranslateModeChange(SN_TranslateMode mode)
{
	emit signalTranslateModeChange(mode);
}

void SnMsgCenter::emitIdentifyAdd(SnIdentify* id)
{
	emit signalIdentifyAdd(id);
}

void SnMsgCenter::emitIdentifyDelete(std::vector<SnIdentify*> ids)
{
	emit signalIdentifyDelete(ids);
}











