#ifndef _SD_RENDER_UTIL_H_
#define _SD_RENDER_UTIL_H_ 

#include "FsMacros.h"
#include "math/FsVector2.h"
#include "graphics/FsColor.h"
#include "math/FsMatrix4.h"


namespace SnRenderUtil
{
	void drawLine(Faeris::Vector2 start,Faeris::Vector2 end,float width,Faeris::Color c);
	void drawLine(Faeris::Matrix4* mat,Faeris::Vector2 start,Faeris::Vector2 end,float width,Faeris::Color c);


	void drawRectangle(Faeris::Vector2 start,Faeris::Vector2 end,Faeris::Color c);
	void drawRectangle(Faeris::Matrix4* mat,Faeris::Vector2 start,Faeris::Vector2 end,Faeris::Color c);

	void drawTriangle(Faeris::Matrix4* mat,Faeris::Vector2 a,Faeris::Vector2 b,Faeris::Vector2 c,Faeris::Color color);

	void drawCircle(Faeris::Matrix4* mat,float radius,float width,Faeris::Color c,float rad_start,float rad_end);


	void drawRectangleFrame(Faeris::Matrix4* world_max, Faeris::Vector2 start,Faeris::Vector2 end,float width,Faeris::Color c);

	void setProjectionMatrix(Faeris::Matrix4* mat);
	void setWorldMatrix(Faeris::Matrix4* mat);
};

#endif /*_SD_RENDER_UTIL_H_*/

