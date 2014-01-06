#include "core/SdAnimation.h"

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





