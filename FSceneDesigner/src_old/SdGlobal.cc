#include <assert.h>
#include "SdGlobal.h"
#include "SdMsgCenter.h"
#include "core/SdProject.h"
#include "core/SdSprite.h"
#include "core/SdAnimation.h"

SdProject* SdGlobal::m_project=NULL;
SdMsgCenter* SdGlobal::m_msgCenter=NULL;
SdMainWindow* SdGlobal::m_mainWindow=NULL;

void SdGlobal::moduleInit()
{
    m_project=NULL;
    m_msgCenter=new SdMsgCenter;
    m_mainWindow=NULL;
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
    if(m_project)
    {
        delete m_project;
    }
    m_project=proj;

}

SdSprite* SdGlobal::getCurSprite()
{
    SdProject* proj=SdGlobal::getProject();
    assert(proj);
    return proj->getCurSprite();
}


void SdGlobal::setCurSprite(SdSprite* sprite)
{
    SdProject* proj=SdGlobal::getProject();
    assert(proj);
    proj->setCurSprite(sprite);
}

SdAnimation* SdGlobal::getCurAnimation()
{
    SdSprite* sprite=SdGlobal::getCurSprite();
    assert(sprite);
    return sprite->getCurAnimation();
}

void SdGlobal::setCurAnimation(SdAnimation* anim)
{
    SdSprite* sprite=SdGlobal::getCurSprite();


    sprite->setCurAnimation(anim);
}


bool SdGlobal::canUndo()
{
    SdProject* proj=SdGlobal::getProject();
    if(proj)
    {
        return proj->canUndo();
    }
    return false;

}

bool SdGlobal::canRedo()
{
    SdProject* proj=SdGlobal::getProject();
    if(proj)
    {
        return proj->canRedo();
    }
    return false;
}



SdMsgCenter* SdGlobal::getMsgCenter()
{
    return m_msgCenter;
}

void SdGlobal::setMsgCenter(SdMsgCenter* center)
{
    m_msgCenter=center;
}

void SdGlobal::setMainWindow(SdMainWindow* win)
{
    m_mainWindow=win;
}

SdMainWindow* SdGlobal::getMainWindow()
{
    return m_mainWindow;
}










