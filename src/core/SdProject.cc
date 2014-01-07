#include <assert.h>

#include "util/SdPath.h"
#include "core/SdProject.h"



SdProject::SdProject(const std::string& name)
{
	init(name);
}

void SdProject::init(const std::string& name)
{
	m_projectDir=SdPath::getDirName(name);
	m_projectName=SdPath::getFileName(name);

	m_resourceDir=m_projectDir;

	m_historyStates=new SdHistoryStates;

	m_imageMgr=new SdImageMgr(m_resourceDir);
	m_iconMgr=new SdIconMgr(m_resourceDir);
}

SdProject::~SdProject()
{
	delete m_imageMgr;
	delete m_iconMgr;
	delete m_historyStates;

	int size=m_sprites.size();

	for(int i=0;i<size;i++)
	{
		delete m_sprites[i];
	}
	m_sprites.clear();
}

SdProject* SdProject::create(const std::string& name);
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
	m_sprites->push_back(ret);
	return ret;
}


void SdSprite::removeSprite(SdSprite* sprite)
{
	int pos=getSpritePos(sprite);
	assert(pos!=-1);
	m_sprites.erase(m_sprites.begin()+pos);
	if(sprite==m_sprites)
	{
		m_sprites=NULL;
	}
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


int SdProject::spritePos(SdSprite* sprite)
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
	m_sprites=sprite;
}


void SdProject::setResourceDir(const std::string& dir)
{
	m_resourceDir=dir;
	m_imageMgr->setResourceDir(dir);
	m_iconMgr->setResourceDir(dir);
}
















