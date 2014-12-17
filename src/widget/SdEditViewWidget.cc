#include <QWheelEvent>
#include "widget/SdEditViewWidget.h"

#include "math/FsMatrix4.h"

#include "FsGlobal.h"
#include "FsFaerisModule.h"
#include "FsGlobal.h"
#include "graphics/FsRender.h"

#include "sys/FsWindow.h"
#include "extends/FsScriptEngine.h"
#include "mgr/FsTextureMgr.h"
#include "mgr/FsFontTTFDataMgr.h"
#include "mgr/FsSprite2DDataMgr.h"

#include "graphics/material/FsMat_V4F_T2F_A1F.h"
#include "graphics/material/FsMat_V4F_T2F.h"
#include "sys/io/FsVFS.h"
#include "sys/io/FsPackage.h"
#include "support/util/FsDict.h"
#include "support/util/FsArray.h"
#include "support/util/FsScriptUtil.h"

SdEditViewWidget::SdEditViewWidget()
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


SdEditViewWidget::~SdEditViewWidget()
{

}
	



void SdViewEditWidget::initializeGL()
{
	if(glewInit()!=GLEW_OK)
	{
		FS_TRACE_WARN("Create GlEW Failed");
    }

    VFS::moduleInit();

    Render* render=Render::create();
    Global::setRender(render);

    TextureMgr* tex_mgr=TextureMgr::create();
    Global::setTextureMgr(tex_mgr);


    FontTTFDataMgr* font_mgr=FontTTFDataMgr::create();
    Global::setFontTTFDataMgr(font_mgr);

}


void SdViewEditWidget::resizeGL(int width,int height)
{
	Matrix4 mat;
	mat.makeOrthographic(-width/2,width/2,-height/2,height/2,-100,100);
	Global::render->setProjectionMatrix(&mat);
	Global::render->setViewport(0,0,width,height);
}


void  SdViewEditWidget::paintGL()
{
    Global::render()->setClearColor(m_backgroundColor);
    Global::render()->clear();

	Matrix4 mat;
	mat.makeCompose(Vector3(m_translate.x,m_translate.y,0),
					Vector3(0,0,0),FS_EULER_XYZ,
					Vector3(m_zoom,m_zoom,1));

	Global::render->pushMatrix(&mat);

	if(m_showGrid)
	{
		--drawGrid();
	}
	if(m_showAxis)
	{
		--drawAxis();
	}

	Global::render->popMatrix();
}




