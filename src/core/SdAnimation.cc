#include "core/SdAnimation.h"
#include "timeline/SdTimeLine.h"

SdAnimation::SdAnimation()
{
}

SdAnimation::~SdAnimation()
{
}




void SdAnimation::setName(std::string name)
{
	m_name=name;
}

std::string SdAnimation::getName()
{
	return m_name;
}


int SdAnimation::getTimeLineNu()
{
	return m_timelines.size();
}

SdTimeLine* SdAnimation::getTimeLine(int index)
{
	return m_timelines[index];
}

SdTimeLine* SdAnimation::createTimeLine()
{
	return createTimeLine("timeline1");
}

SdTimeLine* SdAnimation::createTimeLine(const char* name)
{
	SdTimeLine* timeline=new SdTimeLine;
	timeline->setName(name);
	m_timelines.push_back(timeline);
	return timeline;
}










