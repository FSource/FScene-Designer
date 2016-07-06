#include <QWheelEvent>
#include "widget/SnEditViewWidget.h"


#include "FsGlobal.h"
#include "FsFaerisModule.h"
#include "FsGlobal.h"
#include "graphics/FsRenderDevice.h"

#include "sys/FsWindow.h"
#include "extends/FsScriptEngine.h"
#include "mgr/FsTextureMgr.h"

#include "sys/io/FsVFS.h"
#include "sys/io/FsPackage.h"
#include "support/util/FsDict.h"
#include "support/util/FsArray.h"
#include "support/util/FsScriptUtil.h"

#include "util/SnRenderUtil.h"


SnEditViewWidget::SnEditViewWidget()
{
	m_translate=Vector2(0,0);
	m_zoom=1.0f;

	m_showAxis=true;
	m_showGrid=true;

	m_gridSize=Vector2(32,32);

	m_gridColorA=Color(100,100,100);
    m_gridColorB=Color(70,70,70);

	m_backgroundColor=Color::BLACK;

	m_spaceDown=false;

	setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

}


SnEditViewWidget::~SnEditViewWidget()
{

}
	



void SnEditViewWidget::initializeGL()
{

	if(glewInit()!=GLEW_OK)
	{
		FS_TRACE_WARN("Create GlEW Failed");
    }


    VFS::moduleInit();

    RenderDevice* render=RenderDevice::create();
    Global::setRenderDevice(render);

    TextureMgr* tex_mgr=TextureMgr::create();
    Global::setTextureMgr(tex_mgr);


    FontTTFMgr* font_mgr=FontTTFMgr::create();
    Global::setFontTTFMgr(font_mgr);

	FontBitmapMgr* font_bmp_mgr=FontBitmapMgr::create();
	FS_NO_REF_DESTROY(font_bmp_mgr);
	Global::setFontBitmapMgr(font_bmp_mgr);


	Sprite2DDataMgr* sprite_mgr=Sprite2DDataMgr::create();
	FS_NO_REF_DESTROY(sprite_mgr);
	Global::setSprite2DDataMgr(sprite_mgr);


	ProgramSourceMgr* prog_s_mgr=ProgramSourceMgr::create();
	FS_NO_REF_DESTROY(prog_s_mgr);
	prog_s_mgr->loadPreDefineShader();
	Global::setProgramSourceMgr(prog_s_mgr);

	FelisScriptMgr* flis_mgr=FelisScriptMgr::create();
	FS_NO_REF_DESTROY(flis_mgr);
	Global::setFelisScriptMgr(flis_mgr);


	ClassMgr* cls_mgr=ClassMgr::create();
	FS_NO_REF_DESTROY(cls_mgr);
	Global::setClassMgr(cls_mgr);
	cls_mgr->preRegisterClass();


}


void SnEditViewWidget::resizeGL(int width,int height)
{
	Matrix4 mat;
	mat.makeOrthographic(-width/2,width/2,-height/2,height/2,-100,100);
    SnRenderUtil::setProjectionMatrix(&mat);
	
	//Global::renderDevice()->setViewMatrix(&Matrix4::IDENTITY);
    Global::renderDevice()->setViewport(0,0,width,height);
}


void  SnEditViewWidget::paintGL()
{
    Global::renderDevice()->setClearColor(m_backgroundColor);
    Global::renderDevice()->clear();

	Matrix4 mat;
	mat.makeCompose(Vector3(m_translate.x,m_translate.y,0),
                    Vector3(0,0,0),E_EulerOrientType::XYZ,
					Vector3(m_zoom,m_zoom,1));

	SnRenderUtil::setWorldMatrix(&mat);

	if(m_showGrid)
	{
        drawGrid();
	}
	if(m_showAxis)
	{
        drawAxis();
	}

}





void SnEditViewWidget::drawAxis()
{
	Vector2 a,b;
	getEditArea(&a,&b);
    SnRenderUtil::drawLine(Vector2(a.x,0),Vector2(b.x,0),1,Color::RED);
    SnRenderUtil::drawLine(Vector2(0,a.y),Vector2(0,b.y),1,Color::BLUE);
}
void SnEditViewWidget::drawGrid()
{
	Vector2 a,b;
	getEditArea(&a,&b);

	int min_x=floor(a.x/m_gridSize.x);
	int max_x=ceil(b.x/m_gridSize.x);

	int min_y=floor(a.y/m_gridSize.y);
	int max_y=float(b.y/m_gridSize.y);

	for(int i=min_x-1;i<=max_x;i++)
	{
		for(int j=min_y-1;j<=max_y;j++)
		{
			Vector2 start=Vector2(i*m_gridSize.x,j*m_gridSize.y);
            Vector2 end=Vector2((i+1)*m_gridSize.x,(j+1)*m_gridSize.y);

			if((i+j)%2)
			{
				SnRenderUtil::drawRectangle(start,end,m_gridColorA);
			}
			else 
			{
				SnRenderUtil::drawRectangle(start,end,m_gridColorB);
			}
		}
	}
}


Vector2 SnEditViewWidget::toWidgetCoord(Vector2 v)
{
    float rx=v.x;
    float ry=v.y;
    QSize  wsize=size();
    rx=rx*m_zoom+m_translate.x;
    ry=ry*m_zoom+m_translate.y;
    rx=rx+wsize.width()/2;
    ry=wsize.height()/2-ry;

	Vector2 ret;
    ret.x=rx;
    ret.y=ry;
	return ret;
}

Vector2 SnEditViewWidget::toEditCoord(Vector2 v)
{
	float rx=v.x;
	float ry=v.y;
	QSize wsize=size();

	rx=rx-wsize.width()/2;
	ry=wsize.height()/2-ry;

	Vector2 ret;
	ret.x=(rx-m_translate.x)/m_zoom;
	ret.y=(ry-m_translate.y)/m_zoom;
	return ret;
}


void SnEditViewWidget::getEditArea(Vector2* a,Vector2* b)
{
	QSize wsize=size();
    Vector2 start=toEditCoord(Vector2(0,wsize.height()));
    Vector2 end=toEditCoord(Vector2(wsize.width(),0));

	a->x=start.x;
	a->y=start.y;

	b->x=end.x;
	b->y=end.y;
}

void SnEditViewWidget::setTranslate(Vector2 t)
{
	m_translate=t;
}
Vector2 SnEditViewWidget::getTranslate()
{
	return m_translate;
}
void SnEditViewWidget::setZoom(float s)
{
	m_zoom=s;
}

float SnEditViewWidget::getZoom()
{
	return m_zoom;
}
void SnEditViewWidget::resetZoomTranslate()
{
	m_zoom=1.0f;
	m_translate=Vector2(0.0f,0.0f);
}





void SnEditViewWidget::wheelEvent(QWheelEvent* event)
{
    float detal;

    float zoom=m_zoom;
    float x=event->x();
    float y=event->y();

    QSize wsize=size();
    x=x-wsize.width()/2;
    y=wsize.height()/2-y;

    float rx=(x-m_translate.x)/zoom;
    float ry=(y-m_translate.y)/zoom;

    detal=event->delta()>0?1.1f:0.9f;
    m_zoom*=detal;
	if(m_zoom<0.10f)
	{
		m_zoom=0.10f;
	}

    float tx=x-rx*m_zoom;
    float ty=y-ry*m_zoom;
    m_translate=Vector2(tx,ty);

    update();
}

void SnEditViewWidget::mouseMoveEvent(QMouseEvent* event)
{
	float dx=event->x()-m_lastpos.x();
	float dy=event->y()-m_lastpos.y();

	if(event->buttons()&Qt::LeftButton)
	{
		if(m_spaceDown)
		{
			setTranslate(Vector2(m_translate.x+dx,m_translate.y-dy));
			m_lastpos=event->pos();
			update();
			return;
		}
	}

	m_lastpos=event->pos();
}

void SnEditViewWidget::mousePressEvent(QMouseEvent* event)
{
	if(m_spaceDown)
	{
		m_lastpos=event->pos();
		return;
	}
	m_lastpos=event->pos();
	
}

void SnEditViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if(m_spaceDown)
	{
		m_lastpos=event->pos();
		return;
	}
	m_lastpos=event->pos();
}

void SnEditViewWidget::keyPressEvent(QKeyEvent* event)
{
	if(event->key()==Qt::Key_Space)
	{
		m_spaceDown=true;
		m_prevCursor=cursor();
        setCursor(Qt::ClosedHandCursor);
        update();
		return ;
	}

}
void SnEditViewWidget::keyReleaseEvent(QKeyEvent* event)
{
	if(event->key()==Qt::Key_Space)
	{
		m_spaceDown=false;
		setCursor(m_prevCursor);
        m_prevCursor=Qt::ArrowCursor;
        update();
		return ;
	}
}


void SnEditViewWidget::onZoomIn()
{
	 m_zoom*=1.1f;
	 update();
}
void SnEditViewWidget::onZoomOut()
{
	m_zoom*=0.9f;
	if(m_zoom<0.1f)
	{
		m_zoom=0.1f;
	}

	update();
}
