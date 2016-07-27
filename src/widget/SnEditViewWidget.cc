#include <QWheelEvent>
#include "widget/SnEditViewWidget.h"
#include "core/SnScene.h"
#include "core/SnProject.h"
#include "SnGlobal.h"
#include "operator/SnDataOperator.h"

#include "FsGlobal.h"
#include "FsFaerisModule.h"
#include "FsGlobal.h"
#include "graphics/FsRenderDevice.h"

#include "stage/layer/FsLayer2D.h"
#include "sys/FsWindow.h"
#include "extends/FsScriptEngine.h"
#include "mgr/FsTextureMgr.h"

#include "sys/io/FsVFS.h"
#include "sys/io/FsPackage.h"
#include "support/util/FsDict.h"
#include "support/util/FsArray.h"
#include "support/util/FsScriptUtil.h"

#include "util/SnRenderUtil.h"
#include "controller/SnViewMoveController.h"

#include "controller/SnSelectController.h"
#include "controller/SnTranslateController.h"
#include "controller/SnRotateController.h"
#include "controller/SnResizeController.h"
#include "controller/SnScaleController.h"

#include "SnThemeConfig.h"


SnEditViewWidget::SnEditViewWidget()
{
	m_translate=Vector2(0,0);
	m_zoom=1.0f;

	m_showAxis=true;
	m_showGrid=true;

	m_gridSize=Vector2(32,32);
	m_editMode=SN_EditMode::TRANSALTE;
	m_translateMode=SN_TranslateMode::LOCAL;

	m_gridColorA=Color(100,100,100);
    m_gridColorB=Color(70,70,70);

	m_backgroundColor=Color::BLACK;

	m_spaceDown=false;

	setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

	m_controller=NULL;
	m_moveViewController=new SnViewMoveController();
	m_selectController=new SnSelectController;

	m_translateController=new SnTranslateController(SN_TranslateMode::LOCAL);
	m_wtranslateController=new SnTranslateController(SN_TranslateMode::WORLD);

	m_rotateController=new SnRotateController();

	m_resizeController=new SnResizeController();

	m_scaleController=new SnScaleController();

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


	FsFaeris_LoadSysResource();


}

void SnEditViewWidget::updateViewMatrix()
{

	Vector2 a,b;
	getEditArea(&a,&b);
	float x=a.x;
	float y=a.y;
	float width=b.x-a.x;
	float height=b.y-a.y;

	Matrix4 mat;
	mat.makeOrthographic(
			x,
			x+width,
			y,
			y+height,
			-1024,
			1024);

	SnRenderUtil::setProjectionMatrix(&mat);

}

void SnEditViewWidget::resizeGL(int width,int height)
{
	updateViewMatrix();
	//Global::renderDevice()->setViewMatrix(&Matrix4::IDENTITY);
	Global::renderDevice()->setViewport(0,0,width,height);
}


void  SnEditViewWidget::paintGL()
{
	updateViewMatrix();
	Global::renderDevice()->setClearColor(m_backgroundColor);
	Global::renderDevice()->clear();
	
	SnRenderUtil::setWorldMatrix(&Matrix4::IDENTITY);

	if(m_showGrid)
	{
		drawGrid();
	}
	if(m_showAxis)
	{
		drawAxis();
	}


	drawScene();
	drawSelectIdentify();
	if(m_controller)
	{
		m_controller->onDraw(this);
	}
	else
	{
		drawEditModeInfo();
	}
}


void SnEditViewWidget::setController(SnController* en)
{
	if(m_controller==en)
	{
		return;
	}

	if(m_controller!=NULL)
	{
		m_controller->onUnload(this);
		m_controller=NULL;
	}

	m_controller=en;
	if(m_controller)
	{
		m_controller->onLoad(this);
	}

}


void SnEditViewWidget::drawSelectIdentify()
{
	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	int size=ids.size();
	for(int i=0;i<size;i++)
	{
		SnIdentify* id=ids[i];
		if(dynamic_cast<Entity2D*>(id))
		{
			Entity2D* en=dynamic_cast<Entity2D*>(id);
			Matrix4* mat=en->getWorldMatrix();
			float minx,maxx,miny,maxy;
			en->getBoundSize2D(&minx,&maxx,&miny,&maxy);
			SnRenderUtil::drawRectangleFrame(mat,Vector2(minx,miny),Vector2(maxx,maxy),SnThemeConfig::IDENTIFY_SELECT_OUT_LINE_WIDTH,SnThemeConfig::IDENTIFY_SELECT_OUT_LINE_COLOR);
		}
	}
}



void SnEditViewWidget::drawAxis()
{
	Vector2 a,b;
	getEditArea(&a,&b);
	SnRenderUtil::drawLine(Vector2(a.x,0),Vector2(b.x,0),SnThemeConfig::VIEW_AXIS_WIDTH,SnThemeConfig::VIEW_AXIS_X_COLOR);
	SnRenderUtil::drawLine(Vector2(0,a.y),Vector2(0,b.y),SnThemeConfig::VIEW_AXIS_WIDTH,SnThemeConfig::VIEW_AXIS_Y_COLOR);
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

void SnEditViewWidget::drawScene()
{
	RenderDevice* render=Global::renderDevice();
	SnScene* scene=SnGlobal::dataOperator()->getCurScene();
	if(scene==NULL)
	{
		return;
	}

	int layer_nu=scene->layerNu();
	for(int i=0;i<layer_nu;i++)
	{
		Faeris::Layer2D* l=dynamic_cast<Faeris::Layer2D*>(scene->getLayer(i));
		Vector2 a,b;
		getEditArea(&a,&b);
		float x=a.x;
		float y=a.y;
		float width=b.x-a.x;
		float height=b.y-a.y;

		l->setViewArea(x,y,width,height);
	}

	scene->draw(render);
}

void SnEditViewWidget::drawEditModeInfo()
{
	if(m_editMode==SN_EditMode::TRANSALTE)
	{
		drawTranslateInfo(SnThemeConfig::TRANSLATE_CONTROLLER_CENTER_POINT_COLOR,
				SnThemeConfig::TRANSLATE_CONTROLLER_X_AXIS_COLOR,
				SnThemeConfig::TRANSLATE_CONTROLLER_Y_AXIS_COLOR,m_translateMode);
	}
	else if(m_editMode==SN_EditMode::ROTATE)
	{
		drawRotateInfo(SnThemeConfig::ROTATE_CONTROLLER_OUT_LINE_COLOR, 0);
	}
	else if(m_editMode==SN_EditMode::RESIZE)
	{
		drawResizeInfo(Color(),-1);
	}
	else if(m_editMode==SN_EditMode::SCALE)
	{
		drawScaleInfo(SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_X_AXIS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_Y_AXIS_COLOR,
				SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG,
				SnThemeConfig::SCALE_CONTROLLER_AXIS_HIT_LONG
				);
	}

}

void SnEditViewWidget::drawResizeInfo(Color c,int hit_pos)
{

	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	int size=ids.size();
	if(size==0)
	{
		return;
	}

	SnIdentify* id=ids[0];
	Entity2D* en=dynamic_cast<Entity2D*>(id);

	Matrix4 mat=*en->getWorldMatrix();

	Matrix4 mat2=mat;
	//mat2.setScale(Vector3f(1,1,1));

	float minx,maxx,miny,maxy;
	en->getBoundSize2D(&minx,&maxx,&miny,&maxy);

	SnRenderUtil::drawRectangleFrame(&mat,Vector2(minx,miny),Vector2(maxx,maxy),SnThemeConfig::RESIZE_CONTROLLER_OUT_LINE_WIDTH,SnThemeConfig::RESIZE_CONTROLLER_OUT_LINE_COLOR);

	float s_x=mat.getScale().x;
	float s_y=mat.getScale().y;

	float width=SnThemeConfig::RESIZE_CONTROLLER_OUT_LINE_WIDTH;

	float gap_x=SnThemeConfig::RESIZE_CONTROLLER_RECTANCLE_LENGTH/m_zoom/s_x;
	float gap_y=SnThemeConfig::RESIZE_CONTROLLER_RECTANCLE_LENGTH/m_zoom/s_y;

	Faeris::Color t_c=SnThemeConfig::RESIZE_CONTROLLER_OUT_LINE_COLOR;
	Faeris::Color f_c1=SnThemeConfig::RESIZE_CONTROLLER_FILL_COLOR;
	Faeris::Color f_c2=SnThemeConfig::RESIZE_CONTROLLER_FILL_FOCUS_COLOR;


	Faeris::Vector2f v_pos[8][2] ={
		{Vector2(minx-gap_x,miny-gap_y),Vector2(minx+gap_x,miny+gap_y)},
		{Vector2((minx+maxx)/2-gap_x,miny-gap_y),Vector2((minx+maxx)/2+gap_x,miny+gap_y)},
		{Vector2(maxx-gap_x,miny-gap_y),Vector2(maxx+gap_x,miny+gap_y)},
		{Vector2(maxx-gap_x,(miny+maxy)/2-gap_y),Vector2(maxx+gap_x,(miny+maxy)/2+gap_y)},
		{Vector2(maxx-gap_x,maxy-gap_y),Vector2(maxx+gap_x,maxy+gap_y)},
		{Vector2((minx+maxx)/2-gap_x,maxy-gap_y),Vector2((minx+maxx)/2+gap_x,maxy+gap_y)},
		{Vector2(minx-gap_x,maxy-gap_y),Vector2(minx+gap_x,maxy+gap_y)},
		{Vector2(minx-gap_x,(miny+maxy)/2-gap_y),Vector2(minx+gap_x,(miny+maxy)/2+gap_y)},
	};

	for(int i=0;i<8;i++)
	{
		if(i==hit_pos)
		{
			SnRenderUtil::drawRectangle(&mat,v_pos[i][0],v_pos[i][1],f_c2);
		}
		else 
		{
			SnRenderUtil::drawRectangle(&mat,v_pos[i][0],v_pos[i][1],f_c1);
		}
		SnRenderUtil::drawRectangleFrame(&mat2,v_pos[i][0],v_pos[i][1],width,t_c);
	}

}

void SnEditViewWidget::drawScaleInfo(Color cc, Color cx,Color cy,float lx,float ly)
{

	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	int size=ids.size();
	if(size==0)
	{
		return;
	}

	SnIdentify* id=ids[0];
	Entity2D* en=dynamic_cast<Entity2D*>(id);

	Matrix4 mat;
	mat=*en->getWorldMatrix();
	mat.setScale(Vector3(1,1,1));


	float gap=SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_HIT_GAP/m_zoom;

	Vector2f start=Vector2(-gap,-gap);
	Vector2f end=Vector2(gap,gap);

	SnRenderUtil::drawRectangle(&mat,start,end,cc);
	SnRenderUtil::drawRectangleFrame(&mat,start,end,SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_OUT_LINE_WIDTH,SnThemeConfig::SCALE_CONTROLLER_CENTER_POINT_OUT_LINE_COLOR);


	Vector2f axis_x=Vector2f(lx/m_zoom,0);
	Vector2f axis_y=Vector2f(0,ly/m_zoom);

	SnRenderUtil::drawLine(&mat,Vector2(0,0),axis_x,SnThemeConfig::SCALE_CONTROLLER_AXIS_WIDTH,cx);
	SnRenderUtil::drawLine(&mat,Vector2(0,0),axis_y,SnThemeConfig::SCALE_CONTROLLER_AXIS_WIDTH,cy);

	float x1=(lx-SnThemeConfig::SCALE_CONTROLLER_AXIS_RECT_SIZE)/m_zoom;
	float x2=(lx)/m_zoom;

	
	float x3=(ly-SnThemeConfig::SCALE_CONTROLLER_AXIS_RECT_SIZE)/m_zoom;
	float x4=(ly)/m_zoom;

	float y1=(SnThemeConfig::SCALE_CONTROLLER_AXIS_RECT_SIZE/2)/m_zoom;
	float y2=-y1;

	SnRenderUtil::drawRectangle(&mat,Vector2f(x1,y1),Vector2f(x2,y2),cx);
	SnRenderUtil::drawRectangle(&mat,Vector2f(y1,x3),Vector2f(y2,x4),cy);

}



void SnEditViewWidget::drawRotateInfo(Color c,float angle)
{

	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	int size=ids.size();
	if(size==0)
	{
		return;
	}

	SnIdentify* id=ids[0];
	Entity2D* en=dynamic_cast<Entity2D*>(id);

	Matrix4 mat=*en->getWorldMatrix();
	mat.setScale(Vector3(1,1,1));

	float radius=SnThemeConfig::ROTATE_CONTROLLER_RADIUS/m_zoom;


	SnRenderUtil::drawCircle(&mat,radius,SnThemeConfig::ROTATE_CONTROLLER_OUT_LINE_WIDTH,c,10,350);
	SnRenderUtil::drawLine(&mat,Vector2f(0,0),Vector2f(radius,0),SnThemeConfig::ROTATE_CONTROLLER_OUT_LINE_WIDTH,c);

	float tri_x1=(SnThemeConfig::ROTATE_CONTROLLER_RADIUS)/m_zoom;
	float tri_x2=(SnThemeConfig::ROTATE_CONTROLLER_RADIUS+SnThemeConfig::ROTATE_CONTROLLER_TRIANGLE_WIDTH)/m_zoom;

	float tri_y1=(SnThemeConfig::ROTATE_CONTROLLER_TRIANGLE_HEIGHT/2)/m_zoom;
	float tri_y2=-tri_y1;

	SnRenderUtil::drawTriangle(&mat,Vector2(tri_x1,tri_y1),Vector2(tri_x1,tri_y2),Vector2(tri_x2,0),c);
}

void SnEditViewWidget::drawTranslateInfo(Color c,Color c_x,Color c_y,SN_TranslateMode mode)
{
	std::vector<SnIdentify*> ids=SnGlobal::dataOperator()->getSelectedIdentify();
	int size=ids.size();
	if(size==0)
	{
		return;
	}

	SnIdentify* id=ids[0];
	Entity2D* en=dynamic_cast<Entity2D*>(id);

	Matrix4 mat;
	if(mode == SN_TranslateMode::LOCAL)
	{
		mat=*en->getWorldMatrix();
		mat.setScale(Vector3(1,1,1));
	}
	else 
	{
		mat.makeIdentity();
		mat.setTranslate(en->getPositionInWorld());
	}
	/*
	   Vector3 pos=en->getPositionInWorld();
	   float rotate=en->getRotateZ();

	   Matrix4 mat;
	   mat.makeCompose(pos,Vector3(0,0,rotate),E_EulerOrientType::XYZ,Vector3(1,1,1));
	   */

	float gap=SnThemeConfig::TRANSLATE_CONTROLLER_CENTER_POINT_HIT_GAP/m_zoom;

	Vector2f start=Vector2(-gap,-gap);
	Vector2f end=Vector2(gap,gap);

	SnRenderUtil::drawRectangle(&mat,start,end,c);
	SnRenderUtil::drawRectangleFrame(&mat,start,end,SnThemeConfig::TRANSLATE_CONTROLLER_CENTER_POINT_OUT_LINE_WIDTH,SnThemeConfig::TRANSLATE_CONTROLLER_CENTER_POINT_OUT_LINE_COLOR);


	Vector2f axis_x=Vector2f(SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_LONG/m_zoom,0);
	Vector2f axis_y=Vector2f(0,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_LONG/m_zoom);


	SnRenderUtil::drawLine(&mat,Vector2(0,0),axis_x,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_WIDTH,c_x);
	SnRenderUtil::drawLine(&mat,Vector2(0,0),axis_y,SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_WIDTH,c_y);

	float tri_x1=(SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_LONG-SnThemeConfig::TRANSLATE_CONTROLLER_TRIANGLE_WIDTH)/m_zoom;
	float tri_x2=(SnThemeConfig::TRANSLATE_CONTROLLER_AXIS_HIT_LONG)/m_zoom;

	float tri_y1=(SnThemeConfig::TRANSLATE_CONTROLLER_TRIANGLE_HEIGHT/2)/m_zoom;
	float tri_y2=-tri_y1;

	SnRenderUtil::drawTriangle(&mat,Vector2(tri_x1,tri_y1),Vector2(tri_x1,tri_y2),Vector2(tri_x2,0),c_x);
	SnRenderUtil::drawTriangle(&mat,Vector2(tri_y2,tri_x1),Vector2(tri_y1,tri_x1),Vector2(0,tri_x2),c_y);
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

void SnEditViewWidget::translate(Vector2 t)
{
	setTranslate(m_translate+t);
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
	if(m_controller)
	{
		if(!m_controller->onTouchMove(this,event))
		{
			m_controller=NULL;
		}
	}
	update();
}


void SnEditViewWidget::mousePressEvent(QMouseEvent* event)
{
	if(m_controller==NULL)
	{
		switch(m_editMode)
		{
			case SN_EditMode::TRANSALTE:
				{
					if(m_translateMode==SN_TranslateMode::WORLD)
					{
						if(m_wtranslateController->onTouchBegin(this,event))
						{
							setController(m_wtranslateController);
						}
					}
					else 
					{
						if(m_translateController->onTouchBegin(this,event))
						{
							setController(m_translateController);
						}

					}
				}
				break;
			case SN_EditMode::SCALE:
				{
					if(m_scaleController->onTouchBegin(this,event))
					{
						setController(m_scaleController);
					}
				}
				break;
			case SN_EditMode::ROTATE:
				{
					if(m_rotateController->onTouchBegin(this,event))
					{
						setController(m_rotateController);
					}
				}
				break;
			case SN_EditMode::RESIZE:
				{
					if(m_resizeController->onTouchBegin(this,event))
					{
						setController(m_resizeController);
					}
				}
				break;

		}

		if(m_controller==NULL)
		{
			setController(m_selectController);
		}
	}

	if(m_controller)
	{
		if(!m_controller->onTouchBegin(this,event))
		{
			setController(NULL);
		}
	}
	update();
}



void SnEditViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if(m_controller==NULL)
	{
		return;
	}

	if(!m_controller->onTouchEnd(this,event))
	{
		setController(NULL);
	}
	update();
}


void SnEditViewWidget::keyPressEvent(QKeyEvent* event)
{

	switch(event->key())
	{
		case Qt::Key_R:
			SnGlobal::dataOperator()->setEditMode(SN_EditMode::ROTATE);
			break;
		case Qt::Key_S:
			SnGlobal::dataOperator()->setEditMode(SN_EditMode::SCALE);
			break;
		case Qt::Key_T:
			SnGlobal::dataOperator()->setEditMode(SN_EditMode::TRANSALTE);
			break;
		case Qt::Key_F:
			SnGlobal::dataOperator()->setEditMode(SN_EditMode::RESIZE);
			break;
	}


	if(m_controller==NULL)
	{
		if(m_moveViewController->onKeyPressEvent(this,event))
		{
			setController(m_moveViewController);
			update();
		}
	}
}

void SnEditViewWidget::keyReleaseEvent(QKeyEvent* event)
{
	if(m_controller)
	{
		if(!m_controller->onKeyReleaseEvent(this,event))
		{
			setController(NULL);
		}
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

void SnEditViewWidget::onEditModeChange(SN_EditMode mode)
{
	m_editMode=mode;

	update();
}

void SnEditViewWidget::onAxisModeChange(SN_TranslateMode mode)
{
	m_translateMode=mode;
	update();
}


void SnEditViewWidget::slotIdentifyAttributeChange(SnIdentify* /*id*/,const char* /*name*/)
{
	update();
}

void  SnEditViewWidget::slotCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st)
{
	update();
}

void SnEditViewWidget::slotCurProjectChange()
{
	SnProject* proj=SnGlobal::dataOperator()->getCurProject();
	if(proj)
	{
		m_editMode=proj->getEditMode();
		m_translateMode=proj->getTranslateMode();
	}
	update();
}





