#include "timeline/SdTimeLine.h"
#include "timeline/SdSubTimeLineSet.h"

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

void SdTimeLine::setName(const std::string& name)
{
	m_name=name;
}

std::string SdTimeLine::getName()
{
	return m_name;
}












