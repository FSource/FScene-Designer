#ifndef _SD_RENDER_UTIL_H_
#define _SD_RENDER_UTIL_H_

#include "graphics/FsRender.h"
class SdGLRender:public Faeris::Render 
{
	public:
		static SdGLRender* create();

	public:
		void setPenColor(Color c);

		void drawPoint();
		void drawText(const char* text,Color c,)

};



#endif /*_SD_RENDER_UTIL_H_*/




