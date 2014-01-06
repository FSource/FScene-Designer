#ifndef _SD_KEY_FRAME_H_
#define _SD_KEY_FRAME_H_

#include <string>
class SdImage;
class SdRotateKeyFrame 
{
	public:
		SdRotateKeyFrame()
		{
			m_index=0;
			m_angle=0;
		}
	public:
		int m_index;

		float m_angle;
};

class SdScaleKeyFrame 
{
	public:
		/*
		static SdScaleKeyFrame interpolate(SdScaleKeyFrame l,SdScaleKeyFrame r,float value)
		{
		

		}
		*/

	public:
		SdScaleKeyFrame()
		{
			m_index=0;
			m_scaleX=1;
			m_scaleY=1;
		}


	public:
		int m_index;

		float m_scaleX;
		float m_scaleY;
};


class SdTranslateKeyFrame 
{
	public:
		SdTranslateKeyFrame()
		{
			m_index=0;
			m_translateX=0;
			m_translateY=0;
		}
	public:
		int m_index;

		float m_translateX;
		float m_translateY;
};

class SdColorKeyFrame
{
	public:
		SdColorKeyFrame()
		{
			m_index=0;
			m_colorR=255;
			m_colorG=255;
			m_colorB=255;
			m_colorA=255;
		}
	public:
		int m_index;

		int m_colorR;
		int m_colorG;
		int m_colorB;
		int m_colorA;
};

class SdOtherKeyFrame
{
	public:
		SdOtherKeyFrame()
		{
			m_index=0;
			m_image=NULL;
			m_anchorX=0.5;
			m_anchorY=0.5;
			m_texCoordX0=0;
			m_texCoordY0=0;
			m_texCoordX1=1;
			m_texCoordY1=1;
		}

	public:
		int m_index;

		SdImage* m_image;

		bool m_visible;

		float m_anchorX;
		float m_anchorY;

		float m_texCoordX0;
		float m_texCoordY0;
		float m_texCoordX1;
		float m_texCoordY1;
};








#endif /*_SD_KEY_FRAME_H_*/

