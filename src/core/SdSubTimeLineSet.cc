#include "core/SdSubTimeLineSet.h"



SdSubTimeLineSet::SdSubTimeLineSet(bool init)
{
	if (init)
	{
		m_rotateTimeLine=new SdRotateTimeLine;
		m_translateTimeLine=new SdTranslateTimeLine;
		m_scaleTimeLine=new SdScaleTimeLine;
		m_colorTimeLine=new SdColorTimeLine;
		m_otherTimeLine=new SdOtherTimeLine;
	}
	else 
	{
		m_rotateTimeLine=NULL;
		m_translateTimeLine=NULL;
		m_scaleTimeLine=NULL;
		m_colorTimeLine=NULL;
		m_otherTimeLine=NULL;
	}
}

SdSubTimeLineSet::~SdSubTimeLineSet()
{
	if (m_rotateTimeLine)
	{
		delete m_rotateTimeLine;
	}

	if(m_translateTimeLine)
	{
		delete m_translateTimeLine;
	}

	if(m_scaleTimeLine)
	{
		delete m_scaleTimeLine;
	}

	if(m_colorTimeLine)
	{
		delete m_colorTimeLine;
	}

	if(m_otherTimeLine)
	{
		delete m_otherTimeLine;
	}

}


SdSubTimeLineSet* SdSubTimeLineSet::clone()
{

	SdSubTimeLineSet* ret=new SdSubTimeLineSet(false);

	ret->m_translateTimeLine=this->m_translateTimeLine->clone();
	ret->m_rotateTimeLine=this->m_rotateTimeLine->clone();
	ret->m_scaleTimeLine=this->m_scaleTimeLine->clone();
	ret->m_colorTimeLine=this->m_colorTimeLine->clone();
    ret->m_otherTimeLine=this->m_otherTimeLine->clone();
    return ret;


}


