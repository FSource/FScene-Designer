#include "GL/glew.h"
#include "graphics/FsRenderDevice.h"
#include "util/SnRenderUtil.h"
#include "util/SnUtil.h"
#include "FsGlobal.h"


NS_FS_USE

namespace SnRenderUtil
{
	void setProjectionMatrix(Matrix4* mat)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((float*)mat);
		glMatrixMode(GL_MODELVIEW);

	}

	void setWorldMatrix(Matrix4* mat)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf((float*)mat);
		glMatrixMode(GL_MODELVIEW);
	}

	void drawRectangleFrame(Faeris::Matrix4* world_max, Faeris::Vector2 start,Faeris::Vector2 end,float width,Faeris::Color c)
	{
		drawLine(world_max,Vector2(start.x,start.y),Vector2(start.x,end.y),width,c);
		drawLine(world_max,Vector2(start.x,start.y),Vector2(end.x,start.y),width,c);
		drawLine(world_max,Vector2(end.x,end.y),Vector2(end.x,start.y),width,c);
		drawLine(world_max,Vector2(end.x,end.y),Vector2(start.x,end.y),width,c);
	}





	void drawRectangle(Vector2 start,Vector2 end,Color c)
	{

		drawRectangle(&Matrix4::IDENTITY,start,end,c);
	}

	void drawRectangle(Matrix4* mat, Vector2 start,Vector2 end,Color c)
	{
		setWorldMatrix(mat);
		RenderDevice* render=Global::renderDevice();

		/* use default opengl pipeline */

		render->setProgram(NULL);

		render->disableAllAttrArray();


		float x0=SnUtil::fmin(start.x,end.x);
		float y0=SnUtil::fmin(start.y,end.y);

		float x1=SnUtil::fmax(start.x,end.x);
		float y1=SnUtil::fmax(start.y,end.y);

		glColor4f(float(c.r)/255.0f,float(c.g)/255.0f,float(c.b)/255.0f,float(c.a)/255.0f);

		glBegin(GL_TRIANGLES);
		{
			glVertex2f(x0,y0);
			glVertex2f(x1,y0);
			glVertex2f(x1,y1);
			glVertex2f(x1,y1);
			glVertex2f(x0,y1);
			glVertex2f(x0,y0);
		}
		glEnd();
	}

	void drawLine(Vector2 start,Vector2 end,float width,Color c)
	{
		drawLine(&Matrix4::IDENTITY,start,end,width,c);
	}


    void drawLine(Matrix4* max,Vector2 start,Vector2 end,float width,Color c)
	{
		setWorldMatrix(max);
		RenderDevice* render=Global::renderDevice();
		glLineWidth(width);

		/* use default opengl pipeline */
		render->setProgram(NULL);

		render->disableAllAttrArray();
		glColor4f(float(c.r)/255.0f,float(c.g)/255.0f,float(c.b)/255.0f,float(c.a)/255.0f);
		glBegin(GL_LINES);
		{
			glVertex2f(start.x,start.y);
			glVertex2f(end.x,end.y);
		}
		glEnd();
	}


	void drawTriangle(Faeris::Matrix4* mat,Faeris::Vector2 a,Faeris::Vector2 b,Faeris::Vector2 c,Faeris::Color color)
	{

		setWorldMatrix(mat);
		RenderDevice* render=Global::renderDevice();
		/* use default opengl pipeline */
		render->setProgram(NULL);

		render->disableAllAttrArray();
		glColor4f(float(color.r)/255.0f,float(color.g)/255.0f,float(color.b)/255.0f,float(color.a)/255.0f);
		glBegin(GL_TRIANGLES);
		{
			glVertex2f(a.x,a.y);
			glVertex2f(b.x,b.y);
			glVertex2f(c.x,c.y);
		}
		glEnd();
	}

	void drawCircle(Faeris::Matrix4* mat,float radius,float width,Faeris::Color color,float rad_start,float rad_end)
	{
		setWorldMatrix(mat);
		RenderDevice* render=Global::renderDevice();
		/* use default opengl pipeline */
		render->setProgram(NULL);
		glLineWidth(width);

		render->disableAllAttrArray();
		glColor4f(float(color.r)/255.0f,float(color.g)/255.0f,float(color.b)/255.0f,float(color.a)/255.0f);

		int div=90;
		float step=(rad_end-rad_start)/(180)*3.14/div;

		glBegin(GL_LINE_STRIP);
		for(int i=0;i<=div;i++)
		{
			float angle=rad_start/180*3.14+step*i;

			glVertex2f(cos(angle)*radius,sin(angle)*radius);
		}
		glEnd();
	}
}






