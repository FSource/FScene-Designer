#include <assert.h>
#include "core/SdSprite.h"
#include "core/SdAnimation.h"

int SdSprite::getClassType()
{
	return  SD_CLASS_SPRITE;
}

const char* SdSprite::className()
{
	return "SdSprite";
}


SdSprite::SdSprite(const std::string& name)
{
	m_attr.name=name;
	m_curAnimation=NULL;
	m_project=NULL;
}


SdSprite::~SdSprite()
{
	int size=m_animations.size();
	for(int i=0;i<size;i++)
	{
		delete m_animations[i];

	}
}

void SdSprite::setAttribute(const SdSpriteAttribute& attr)
{
	m_attr=attr;
}


SdSpriteAttribute SdSprite::getAttribute()
{
	return m_attr;
}



void SdSprite::setName(const std::string& name)
{
	m_attr.name=name;
}

std::string SdSprite::getName()
{
	return m_attr.name;
}


SdProject* SdSprite::getProject()
{
	return m_project;
}

void SdSprite::setProject(SdProject* proj)
{
	m_project=proj;
}

SdAnimation* SdSprite::createAnimation(const std::string& name)
{
	SdAnimation* anim=new SdAnimation(name);
	anim->setSprite(this);
	return anim;
}
void SdSprite::removeAnimation(SdAnimation* anim)
{
	int pos=getAnimationPos(anim);
	assert(pos!=-1);
	m_animations.erase(m_animations.begin()+pos);

	if(m_curAnimation=anim)
	{
		m_curAnimation=NULL;
	}

}

void SdSprite::addAnimation(int pos,SdAnimation* anim)
{
	m_animations.insert(m_animations.begin()+pos,anim);
	anim->setSprite(this);
}

void SdSprite::addAnimation(SdAnimation* anim)
{
	m_animations.push_back(anim);
	anim->setSprite(this);
}




int SdSprite::getAnimationNu()
{
	return m_animations.size();
}

SdAnimation* SdSprite::getAnimation(int index)
{
	return m_animations[index];
}

bool SdSprite::hasAnimationWithName(const std::string& name)
{
	int size=m_animations.size();

	for(int i=0;i<size;i++)
	{
		if(m_animations[i]->getName()==name)
		{
			return true;
		}
	}

	return false;
}

bool SdSprite::hasAnimation(SdAnimation* anim)
{
	int pos=getAnimationPos(anim);
	if (pos==-1)
	{
		return false;
	}
	return true;
}


int SdSprite::getAnimationPos(SdAnimation* anim)
{
	int size=m_animations.size();

	for(int i=0;i<size;i++)
	{
		if(m_animations[i]==anim)
		{
			return i;
		}
	}
	return -1;
}


SdAnimation* SdSprite::getCurAnimation()
{
	return m_curAnimation;
}

void SdSprite::setCurAnimation(SdAnimation* anim)
{
	m_curAnimation=anim;
}












































