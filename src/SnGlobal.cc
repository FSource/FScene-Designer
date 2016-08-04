#include <assert.h>
#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnProject.h"
#include "operator/SnDataOperator.h"
#include "operator/SnUiOperator.h"
#include "operator/SnDataOperator.h"

#include "SnIdentifyFactory.h"



SnProject* SnGlobal::m_project=NULL;

SnMsgCenter* SnGlobal::m_msgCenter=NULL;
SnMainWindow* SnGlobal::m_mainWindow=NULL;
SnDataOperator* SnGlobal::m_dataOperator=NULL;
SnUiOperator* SnGlobal::m_uiOperator=NULL;
SnIoOperator* SnGlobal::m_ioOperator=NULL;

SnIdentifyFactory* SnGlobal::m_identifyFactory=NULL;



void SnGlobal::moduleInit()
{
    m_project=NULL;
    m_msgCenter=new SnMsgCenter;

	m_dataOperator=new SnDataOperator();
	m_uiOperator=new SnUiOperator();

	m_identifyFactory=new SnIdentifyFactory();
	m_identifyFactory->preLoadCreatorFuncs();

    m_mainWindow=NULL;
}


void SnGlobal::moduleExit()
{
}




SnProject* SnGlobal::getProject()
{
    return m_project;
}

void SnGlobal::setProject(SnProject* proj)
{
    if(m_project)
    {
		m_project->unRegisterFsGlobalMgr();

        delete m_project;
    }


	proj->registerFsGlobalMgr();
	proj->loadScene();

    m_project=proj;
	

	m_msgCenter->emitCurProjectChange();


}

void SnGlobal::setMainWindow(SnMainWindow* win)
{
    m_mainWindow=win;
}



SnMainWindow* SnGlobal::getMainWindow()
{
    return m_mainWindow;
}

SnMsgCenter* SnGlobal::msgCenter()
{
	return m_msgCenter;
}

SnDataOperator* SnGlobal::dataOperator()
{
	return m_dataOperator;
}

SnUiOperator* SnGlobal::uiOperator()
{
	return m_uiOperator;
}

SnIoOperator* SnGlobal::ioOperator()
{
	return m_ioOperator;
}

SnIdentifyFactory* SnGlobal::identifyFactory()
{
	return m_identifyFactory;
}


