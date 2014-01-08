#ifndef _SD_SUB_TIME_LINE_H_
#define _SD_SUB_TIME_LINE_H_

#include <vector>
#include "core/SdKeyFrame.h"

class SdSubTimeLineUiData;
template < typename TKeyFrame > 
class SdSubTimeLine 
{
	public:
        SdSubTimeLine(){}
        ~SdSubTimeLine(){}

	public:
		void insertKeyFrame(TKeyFrame keyframe);
		void interpolatedKeyFrame(int frame);

		/* key fame */
        int getKeyFrameNu()
        {
            return m_keyframes.size();
        }

        TKeyFrame getKeyFrame(int index)
        {
            return m_keyframes[index];
        }

		/* frame */
		int getFrameNu();
		TKeyFrame getFrame(int index);
        TKeyFrame getInterpolateFrame(float index);

        SdSubTimeLine<TKeyFrame>* clone()
        {
            SdSubTimeLine<TKeyFrame>*  ret=new SdSubTimeLine<TKeyFrame>;
            ret->m_keyframes=this->m_keyframes;
            return ret;

        }



	private:
		std::vector<TKeyFrame> m_keyframes;
};

typedef SdSubTimeLine<SdRotateKeyFrame> SdRotateTimeLine;
typedef SdSubTimeLine<SdTranslateKeyFrame> SdTranslateTimeLine;
typedef SdSubTimeLine<SdScaleKeyFrame> SdScaleTimeLine;
typedef SdSubTimeLine<SdColorKeyFrame> SdColorTimeLine;
typedef SdSubTimeLine<SdOtherKeyFrame> SdOtherTimeLine;


#endif /*_SD_SUB_TIME_LINE_H_*/




