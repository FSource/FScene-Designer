#include "core/SdAnimation.h"
#include "timeline/SdTimeLine.h"

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





void SdAnimation::setName(std::string name)
{
	m_attr.m_name=name;
}

std::string SdAnimation::getName()
{
	return return m_attr.m_name;
}

SdSprite* SdAnimation::getSprite()
{
	return m_sprite;
}

void SdAnimation::setSprite(SdSprite* sprite)
{
	return m_sprite=sprite;
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

int SdAnimation::getTimeLineNu()
{
	return m_timelines.size();
}

SdTimeLine* SdAnimation::getTimeLine(int index)
{
	return m_timelines[index];
}


bool SdTimeLine::hasTimeLineWithName(const std::string& name)
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

bool SdTimeLine::hasTimeLine(SdTimeLine* line)
{
	int pos=getTimeLinePos(line);
	if(pos==-1)
	{
		return false;
	}
	return true;
}

int SdTimeLine::getTimeLinePos(SdTimeLine* line)
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











