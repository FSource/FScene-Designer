#include <assert.h>
#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnProject.h"

SnProject* SnGlobal::m_project=NULL;
SnMsgCenter* SnGlobal::m_msgCenter=NULL;
SnMainWindow* SnGlobal::m_mainWindow=NULL;


void SnGlobal::moduleInit()
{
    m_project=NULL;
    m_msgCenter=new SnMsgCenter;
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
        delete m_project;
    }
    m_project=proj;
}

void SnGlobal::setMainWindow(SnMainWindow* win)
{
    m_mainWindow=win;
}

SnMainWindow* SnGlobal::getMainWindow()
{
    return m_mainWindow;
}
