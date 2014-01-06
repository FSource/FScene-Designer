#include "timeline/SdTimeLine.h"
#include "timeline/SdSubTimeLineSet.h"



SdTimeLine::SdTimeLine()
{
	m_visible=true;
	m_select=false;
	m_expand=false;

	m_subTimeSet=new SdSubTimeLineSet;
	m_uiData=NULL;
}

SdTimeLine::~SdTimeLine()
{
	delete m_subTimeSet;
}




