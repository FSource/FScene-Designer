#include "SdGlobal.h"
#include "SdMsgCenter.h"

SdProject* SdGlobal::m_project=NULL;
SdMsgCenter* SdGlobal::m_msgCenter=NULL;


void SdGlobal::moduleInit()
{
	m_project=NULL;
	m_msgCenter=new SdMsgCenter;
}

void SdGlobal::moduleExit()
{

}



SdProject* SdGlobal::getProject()
{
	return m_project;
}

void SdGlobal::setProject(SdProject* proj)
{
	m_project=proj;
}


SdMsgCenter* SdGlobal::getMsgCenter()
{
	return m_msgCenter;
}

void SdGlobal::setMsgCenter(SdMsgCenter* center)
{
	m_msgCenter=center;
}










