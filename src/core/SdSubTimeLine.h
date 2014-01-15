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
		void insertKeyFrame(TKeyFrame keyframe)
		{
			int size=m_keyframes.size();
			int insert_pos=0;
			for(int i=0;i<size;i++)
			{
				if(keyframe.m_index==m_keyframes[i].m_index)
				{
					m_keyframes[i]=keyframe;
					return;
				}

			if(keyframe.m_index<m_keyframes[i].m_index)
			{
					insert_pos=i;
				}
			}
			m_keyframes.insert(m_keyframes.begin()+insert_pos,keyframe);
		}


		int frameToKeyFramePos(int index)
		{
			int size=m_keyframes.size();
			for(int i=0;i<size;i++)
			{
				if(keyframe.m_index==index)
				{
					return i;
				}

			}
			return -1;
		}
		int frameToNearestPreKeyFramePos(int index)
		{
			int size=m_keyframes.size();
			int pos=-1;
			for(int i=0;i<size;i++)
			{
				if(index<=m_keyframes[i].m_index)
				{
					pos=i;
				}

			}
			return pos;
		}


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
		int getFrameNu()
		{
			int size=m_keyframes.size();
			if(size==0)
			{
				return 0;
			}

			return m_keyframes[size-1].m_index;
		}

		TKeyFrame getNearestPreFrame(int index)
		{
			int size=m_keyframes.size();
			if(size==0)
			{
				return TKeyFrame;
			}
		}

        TKeyFrame getInterpolateFrame(float index)
		{
			return interpolatedKeyFrame(index);
		}

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




