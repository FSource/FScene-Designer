#include <assert.h>

#include "util/SdPathUtil.h"
#include "core/SdProject.h"
#include "core/SdImageMgr.h"
#include "core/SdSprite.h"



SdProject::SdProject(const std::string& name)
{
	init(name);
}

void SdProject::init(const std::string& name)
{
    m_projectDir=SdPathUtil::getDirName(name);
    m_projectName=SdPathUtil::getFileName(name);

	m_resourceDir=m_projectDir;

//	m_historyStates=new SdHistoryStates;

	m_imageMgr=new SdImageMgr(m_resourceDir);
//	m_iconMgr=new SdIconMgr(m_resourceDir);
}

SdProject::~SdProject()
{
	delete m_imageMgr;
//	delete m_iconMgr;
    //delete m_historyStates;

	int size=m_sprites.size();

	for(int i=0;i<size;i++)
	{
		delete m_sprites[i];
	}
	m_sprites.clear();
}

SdProject* SdProject::create(const std::string& name)
{
	return new SdProject(name);
}


std::string SdProject::getName()
{
	return m_projectName;
}


SdSprite* SdProject::createSprite(const std::string& name)
{
	SdSprite* ret=new SdSprite(name);
	ret->setProject(this);
    m_sprites.push_back(ret);
	return ret;
}


void SdProject::removeSprite(SdSprite* sprite)
{
	int pos=getSpritePos(sprite);
	assert(pos!=-1);
	m_sprites.erase(m_sprites.begin()+pos);
    if(sprite==m_curSprite)
	{
        m_curSprite=NULL;
	}
}
void SdProject::addSprite(int pos,SdSprite* sprite)
{
	m_sprites.insert(m_sprites.begin()+pos,sprite);
	sprite->setProject(this);
}

void SdProject::addSprite(SdSprite* sprite)
{
	m_sprites.push_back(sprite);
	sprite->setProject(this);
}


int SdProject::getSpriteNu()
{
	return m_sprites.size();
}

SdSprite* SdProject::getSprite(int index)
{
	return m_sprites[index];
}







bool SdProject::hasSpriteWithName(const std::string& name)
{
	int size=m_sprites.size();
	for(int i=0;i<size;i++)
	{
		if (m_sprites[i]->getName()==name)
		{
			return true;
		}
	}
	return false;
}


bool SdProject::hasSprite(SdSprite* sprite)
{
	int size=m_sprites.size();
	for(int i=0;i<size;i++)
	{
		if(m_sprites[i]==sprite)
		{
			return true;
		}
	}
	return false;
}


int SdProject::getSpritePos(SdSprite* sprite)
{
	int size=m_sprites.size();
	for(int i=0;i<size;i++)
	{
		if(m_sprites[i]==sprite)
		{
			return i;
		}
	}
	return -1;
}


SdSprite* SdProject::getCurSprite()
{
	return m_curSprite;
}

void SdProject::setCurSprite(SdSprite* sprite)
{
    m_curSprite=sprite;
}


void SdProject::setResourceDir(const std::string& dir)
{
	m_resourceDir=dir;
	m_imageMgr->setResourceDir(dir);
	m_imageMgr->refresh();

    //m_iconMgr->setResourceDir(dir);
    //m_iconMgr->refresh();
}

std::string SdProject::getResourceDir()
{
	return m_resourceDir;
}


SdImageMgr* SdProject::getImageMgr()
{
	return m_imageMgr;
}

SdIconMgr* SdProject::getIconMgr()
{
	return m_iconMgr;
}
















