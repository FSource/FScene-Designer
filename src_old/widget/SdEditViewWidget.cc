#include <QWheelEvent>
#include "widget/SdEditViewWidget.h"

#include "math/FsMatrix4.h"

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
	



void SdEditViewWidget::initializeGL()
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

}


void SdEditViewWidget::resizeGL(int width,int height)
{
	Matrix4 mat;
	mat.makeOrthographic(-width/2,width/2,-height/2,height/2,-100,100);
    Global::renderDevice()->setProjectionMatrix(&mat);
    Global::renderDevice()->setViewport(0,0,width,height);
}


void  SdEditViewWidget::paintGL()
{
    Global::renderDevice()->setClearColor(m_backgroundColor);
    Global::renderDevice()->clear();

	Matrix4 mat;
	mat.makeCompose(Vector3(m_translate.x,m_translate.y,0),
                    Vector3(0,0,0),E_EulerOrientType::XYZ,
					Vector3(m_zoom,m_zoom,1));

    Global::renderDevice()->pushWorldMatrix();
    Global::renderDevice()->setWorldMatrix(&mat);

	if(m_showGrid)
	{
        drawGrid();
	}
	if(m_showAxis)
	{
        drawAxis();
	}

    Global::renderDevice()->popWorldMatrix();
}




