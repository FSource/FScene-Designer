#ifndef _SD_SUB_TIME_LINE_SET_H_
#define _SD_SUB_TIME_LINE_SET_H_ 

#include "core/SdSubTimeLine.h"

class SdSubTimeLineSet 
{
	public:
		SdSubTimeLineSet(bool init=true);
		~SdSubTimeLineSet();

	public:
		SdSubTimeLineSet* clone();

	public:
		SdRotateTimeLine* m_rotateTimeLine;
		SdTranslateTimeLine* m_translateTimeLine;
		SdScaleTimeLine* m_scaleTimeLine;
		SdColorTimeLine* m_colorTimeLine;
		SdOtherTimeLine* m_otherTimeLine;
};


#endif /*_SD_SUB_TIME_LINE_SET_H_*/



