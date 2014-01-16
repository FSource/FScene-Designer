#include <assert.h>
#include "core/SdAnimation.h"
#include "core/SdTimeLine.h"
#include "SdConfig.h"



int SdAnimation::getClassType()
{
	return SD_CLASS_ANIMATION;
}

const char* SdAnimation::className()
{
	return "SdAnimation";
}

SdAnimation::SdAnimation(const std::string& name)
{
	m_attr.name=name;
	m_attr.playSpeed=SD_ANIMATION_DEFAULT_FPS;
	m_sprite=NULL;
}

SdAnimation::~SdAnimation()
{
	int size=m_timelines.size();
	for(int i=0;i<size;i++)
	{
		delete m_timelines[i];
	}
	m_timelines.clear();
}





void SdAnimation::setName(const std::string& name)
{
    m_attr.name=name;
}

std::string SdAnimation::getName()
{
    return m_attr.name;
}

SdSprite* SdAnimation::getSprite()
{
	return m_sprite;
}

void SdAnimation::setSprite(SdSprite* sprite)
{
    m_sprite=sprite;
}

SdTimeLine* SdAnimation::createTimeLine(const std::string& name)
{
	SdTimeLine* timeline=new SdTimeLine(name);
	timeline->setAnimation(this);
	m_timelines.push_back(timeline);
	return timeline;
}

void SdAnimation::removeTimeLine(SdTimeLine* line)
{
	int pos=getTimeLinePos(line);
	assert(pos!=-1);
	m_timelines.erase(m_timelines.begin()+pos);
}

void SdAnimation::addTimeLine(int pos,SdTimeLine* line)
{
	m_timelines.insert(m_timelines.begin()+pos,line);
}

void SdAnimation::addTimeLine(SdTimeLine* line)
{
	m_timelines.push_back(line);
}

int SdAnimation::getTimeLineNu()
{
	return m_timelines.size();
}

SdTimeLine* SdAnimation::getTimeLine(int index)
{
	return m_timelines[index];
}


bool SdAnimation::hasTimeLineWithName(const std::string& name)
{
	int size=m_timelines.size();
	for(int i=0;i<size;i++)
	{
		if(m_timelines[i]->getName()==name)
		{
			return true;
		}
	}
	return false;
}

bool SdAnimation::hasTimeLine(SdTimeLine* line)
{
	int pos=getTimeLinePos(line);
	if(pos==-1)
	{
		return false;
	}
	return true;
}

int SdAnimation::getTimeLinePos(SdTimeLine* line)
{
	int size=m_timelines.size();
	for(int i=0;i<size;i++)
	{
		if(m_timelines[i]==line)
		{
			return i;
		}
	}
	return -1;
}

void SdAnimation::setPlaySpeed(int fps)
{
	m_attr.playSpeed=fps;
}

int SdAnimation::getPlaySpeed()
{
	return m_attr.playSpeed;
}

void SdAnimation::setAttribute(const SdAnimationAttribute& attr)
{
	m_attr=attr;
}

SdAnimationAttribute SdAnimation::getAttribute()
{
	return m_attr;
}






