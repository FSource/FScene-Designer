#ifndef _SD_SUB_TIME_LINE_H_
#define _SD_SUB_TIME_LINE_H_

#include <vector>
#include "core/SdKeyFrame.h"

class SdSubTimeLineUiData;


template < typename TKeyFrame > 
class SdSubTimeLine 
{
	public:
		enum
		{
			STATE_FLOAT=0,
			STATE_NORMAL,
		};

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

		void beginFloatKeyFrames(int bframe,int eframe)
		{
			m_state=STATE_FLOAT;
			m_floatKeyframes.clear();
			m_floatOffset=0;

			std::vector<TKeyFrame> not_float;
			int size=m_keyframes.size();
			for(int i=0;i<size;i++)
			{
				if (m_keyframes[i].m_index>=bframe && m_keyframes[i].m_index< eframe)
				{
					m_floatKeyframes.push_back(m_keyframes[i]);
				}
				else 
				{
					not_float.push_back(m_keyframes[i]);
				}
			}
			m_keyframes=not_float;
		}

		void setFloatOffset(int offset)
		{
			m_floatOffset=offset;
		}

		void endFloatKeyFrames()
		{
			m_state=STATE_NORMAL;
			int float_nu=m_floatKeyframes.size();
			for(int i=0;i<float_nu;i++)
			{
				TKeyFrame frame=m_floatKeyframes[i];
				frame.m_index+=m_floatOffset;
				insertKeyFrame(frame);
			}
			m_floatKeyframes.clear();
			m_floatOffset=0;
		}

	private:
		int m_state;

		std::vector<TKeyFrame> m_keyframes;
		std::vector<TKeyFrame> m_floatKeyframes;
		int m_floatOffset;
};


typedef SdSubTimeLine<SdRotateKeyFrame> SdRotateTimeLine;
typedef SdSubTimeLine<SdTranslateKeyFrame> SdTranslateTimeLine;
typedef SdSubTimeLine<SdScaleKeyFrame> SdScaleTimeLine;
typedef SdSubTimeLine<SdColorKeyFrame> SdColorTimeLine;
typedef SdSubTimeLine<SdOtherKeyFrame> SdOtherTimeLine;


#endif /*_SD_SUB_TIME_LINE_H_*/














