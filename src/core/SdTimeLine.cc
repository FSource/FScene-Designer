#include "core/SdTimeLine.h"
#include "core/SdSubTimeLineSet.h"

SdTimeLine::SdTimeLine(const std::string& name)
{
	m_visible=true;
	m_select=false;
	m_expand=false;

	m_subTimeSet=new SdSubTimeLineSet;
	m_name=name;
	m_animation=NULL;
}

SdTimeLine::~SdTimeLine()
{
	delete m_subTimeSet;
}

void SdTimeLine::setName(const std::string& name)
{
	m_name=name;
}

std::string SdTimeLine::getName()
{
	return m_name;
}

bool SdTimeLine::getVisible()
{
	return m_visible;
}

void SdTimeLine::setVisible(bool v)
{
	m_visible=v;
}

bool SdTimeLine::getSelect()
{
	return m_select;
}

void SdTimeLine::setSelect(bool v)
{
	m_select=v;
}

bool SdTimeLine::getExpand()
{
	return m_expand;
}
void SdTimeLine::setExpand(bool v)
{
	m_expand=v;
}


void SdTimeLine::setAnimation(SdAnimation* anim)
{
	m_animation=anim;
}



SdAnimation* SdTimeLine::getAnimation()
{
	return m_animation;
}




SdScaleTimeLine* SdTimeLine::getScaleTimeLine()
{
	return m_subTimeSet->m_scaleTimeLine;
}
void SdTimeLine::setScaleTimeLine(SdScaleTimeLine* line)
{
	if(m_subTimeSet->m_scaleTimeLine)
	{
		delete m_subTimeSet->m_scaleTimeLine;
	}
	m_subTimeSet->m_scaleTimeLine=line;
}



SdRotateTimeLine* SdTimeLine::getRotateTimeLine()
{
	return m_subTimeSet->m_rotateTimeLine;
}

void SdTimeLine::setRotateTimeLine(SdRotateTimeLine* line)
{
	if(m_subTimeSet->m_rotateTimeLine)
	{
		delete m_subTimeSet->m_rotateTimeLine;
	}
	m_subTimeSet->m_rotateTimeLine=line;
}


SdTranslateTimeLine* SdTimeLine::getTranslateTimeLine()
{
	return m_subTimeSet->m_translateTimeLine;
}

void SdTimeLine::setTranslateTimeLine(SdTranslateTimeLine* line)
{
	if(m_subTimeSet->m_translateTimeLine)
	{
		delete m_subTimeSet->m_translateTimeLine;
	}
	m_subTimeSet->m_translateTimeLine=line;
}


SdColorTimeLine* SdTimeLine::getColorTimeLine()
{
	return m_subTimeSet->m_colorTimeLine;
}
void SdTimeLine::setColorTimeLine(SdColorTimeLine* line)
{
	if(m_subTimeSet->m_colorTimeLine)
	{
		delete m_subTimeSet->m_colorTimeLine;
	}
	m_subTimeSet->m_colorTimeLine=line;
}



SdOtherTimeLine* SdTimeLine::getOtherTimeLine()
{
	return m_subTimeSet->m_otherTimeLine;
}

void SdTimeLine::setOtherTimeLine(SdOtherTimeLine* line)
{
	if(m_subTimeSet->m_otherTimeLine)
	{
		delete m_subTimeSet->m_otherTimeLine;
	}
	m_subTimeSet->m_otherTimeLine=line;
}





















