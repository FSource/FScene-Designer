#include <QTextStream>
#include <QDir>
#include <QFileInfo>

#include "util/SnUtil.h"
#include "core/SnIdentify.h"

#include "stage/entity/FsEntity2D.h"
#include "SnGlobal.h"
#include "SnIdentifyFactory.h"
#include "core/SnLabelTTF.h"
#include "core/SnQuad2D.h"
#include "core/SnLabelBitmap.h"

#include "support/util/FsScriptUtil.h"
#include "support/util/FsDict.h"



NS_FS_USE

namespace  SnUtil 
{

	std::string qtostd(QString value)
	{
		std::string ret=value.toUtf8().constData();
		return ret;
	}

	/*
	QString toProjectPath(const QString& path)
	{
		MdProject* proj=MdOperator::data()->getCurProject();
		assert(proj);
		QString proj_dir=proj->getDirName()+"/";
        assert(path.startsWith(proj_dir));
        QString ret=path;
        ret.remove(0,proj_dir.size());
		return ret;
	}
	*/


	std::string toRelativePath(const char*  root,const char* path)
	{
		QString rel_root=root;

		QString q_path=path;
		assert(q_path.startsWith(rel_root));
		QString ret=q_path;
		ret.remove(0,rel_root.size());

		return ret.toUtf8().constData();
	}


	/* hit info */
	bool identifyInRect(SnIdentify* id,Vector2f start,Vector2f end)
	{
		float minx=start.x ;
		float maxx=end.x;
		float miny=start.y;
		float maxy=end.y;

		if(minx>maxx)
		{
			float t=minx;
			minx=maxx;
			maxx=t;
		}
		if(miny>maxy)
		{
			float t=miny;
			miny=maxy;
			maxy=t;
		}

		
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		float e_maxx,e_minx,e_miny,e_maxy;
		en->getTRSBoundSize2D(&e_minx,&e_maxx,&e_miny,&e_maxy);

		if(e_minx>=minx&&e_maxx<=maxx&&e_miny>=miny&&e_maxy<=maxy)
		{
			return true;
		}
		return false;
	}

	bool identifyHitPoint(SnIdentify* id,Vector2f p)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}
		return en->hit2D(p.x,p.y);
	}




	bool hitIdentityCenterPoint(SnIdentify* id,Vector2f pos,float gap,SN_TranslateMode mode)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		Matrix4* mat=en->getWorldMatrix();
		Vector3 s_info=mat->getScale();
		float gapy=gap/s_info.y;
		float gapx=gap/s_info.x; 


		
		Vector3f t ;
		if(mode ==SN_TranslateMode::LOCAL) 
		{

			t= en->worldToLocal(Vector3f(pos.x,pos.y,0));
		}
		else 
		{
			Vector3f p = en->getPositionInWorld();
			t=Vector3f(pos.x,pos.y,0)-p;
		}

		if(Math::abs(t.x) < gapx)
		{
			if(Math::abs(t.y) < gapy)
			{
				return true;
			}
		}

		return false;
	}

	bool hitIdentityAxisX(SnIdentify* id,Vector2f pos,float width,float length,SN_TranslateMode mode)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		Matrix4* mat=en->getWorldMatrix();

		Vector3 s_info=mat->getScale();
		width=width/s_info.y;
		length=length/s_info.x;

		Vector3f t ;
		if(mode ==SN_TranslateMode::LOCAL) 
		{

			t= en->worldToLocal(Vector3f(pos.x,pos.y,0));
		}
		else 
		{
			Vector3f p = en->getPositionInWorld();
			t=Vector3f(pos.x,pos.y,0)-p;
		}


		if(Math::abs(t.y)< width)
		{
			if(t.x>0&&t.x< length)
			{
				return true;
			}
		}

		return false;
	}

	bool hitIdentityAxisY(SnIdentify* id,Vector2f pos,float width,float length,SN_TranslateMode mode)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		Matrix4* mat=en->getWorldMatrix();

		Vector3 s_info=mat->getScale();
		width=width/s_info.x;
		length=length/s_info.y;

		Vector3f t ;
		if(mode ==SN_TranslateMode::LOCAL) 
		{

			t= en->worldToLocal(Vector3f(pos.x,pos.y,0));
		}
		else 
		{
			Vector3f p = en->getPositionInWorld();
			t=Vector3f(pos.x,pos.y,0)-p;
		}

		if(Math::abs(t.x)<width)
		{
			if(t.y>0&&t.y<length)
			{
				return true;
			}
		}
		return false;
	}


	/* url info */
	bool canCreateIdentifyFromUrl(const char* name)
	{
		if(identifyTypeFromUrl(name)<=SN_CLASS_LAYER2D)
		{
			return false;
		}

		return true;
	}

	int identifyTypeFromUrl(const char* name)
	{
		QFileInfo file(name);

		if(!file.isFile())
		{
			return SN_CLASS_UNKOWN;
		}

		if(!file.exists())
		{
			return SN_CLASS_UNKOWN;
		}


		QString ext=file.suffix();
		if(ext=="png"||ext=="jpg"||ext=="tga"||ext=="jpeg")
		{
			return SN_CLASS_QUAD2D;
		}

		if(ext=="ttf"||ext=="ttc")
		{
			return SN_CLASS_LABEL_TTF;
		}

		if(ext=="fnt")
		{
			return SN_CLASS_LABEL_BMP;
		}

		if(ext=="fst")
		{
			QFile f(name);

			if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  
			{
				return NULL;
			}

			QTextStream txtInput(&f); 
			txtInput.setCodec("UTF-8");

			QString content=txtInput.readAll();
			FsDict* dict=ScriptUtil::parseScriptFromStr(content.toUtf8().constData());

			if(dict==NULL)
			{
				return SN_CLASS_UNKOWN;
			}
			FsString* type_name=dict->lookupString("editClass");
			if(type_name==NULL)
			{
				dict->destroy();
				return SN_CLASS_LAYER2D;
			}

			int type=SN_CLASS_UNKOWN;

			if(type_name->compare("SnEntity2D")==0)
			{
				type=SN_CLASS_ENTITY2D;
			}
			else if(type_name->compare("SnQuad2D")==0)
			{
				type=SN_CLASS_QUAD2D;
			}
			else if(type_name->compare("SnLabelTTF")==0)
			{
				type=SN_CLASS_LABEL_TTF;
			}
			else if(type_name->compare("SnLabelBmp")==0)
			{
				type=SN_CLASS_LABEL_BMP;
			}
			else if(type_name->compare("SnPressButton")==0)
			{
				type=SN_CLASS_PRESS_BUTTON;
			}
			else if(type_name->compare("SnUiWidget")==0)
			{
				type=SN_CLASS_UI_WIDGET;
			}
			else if(type_name->compare("SnPageView")==0)
			{
				type=SN_CLASS_PAGE_VIEW;
			}
			else if(type_name->compare("SnListView")==0)
			{
				type=SN_CLASS_LIST_VIEW;
			}
			else if(type_name->compare("SnScrollView")==0)
			{
				type=SN_CLASS_SCROLL_VIEW;
			}

			dict->destroy();
			return  type;
		}

		return SN_CLASS_UNKOWN;
	}


	SnIdentify* createIdentifyFromUrl(const char* root,const char* relative)
	{
		QFileInfo file(root);

		std::string filename=file.fileName().toUtf8().constData();


		int type=identifyTypeFromUrl(root);
		if(type==SN_CLASS_UNKOWN)
		{
			return NULL;
		}

		if(type==SN_CLASS_QUAD2D)
		{
			SnQuad2D* ret=new SnQuad2D();
			ret->setResourceUrl(relative);
			ret->setObjectName(filename.c_str());
			return ret;
		}
		else if(type==SN_CLASS_LABEL_TTF)
		{
			SnLabelTTF* ret=new SnLabelTTF();
			ret->setFontName(relative);
			ret->setObjectName(filename.c_str());

			return ret;
		}
		else if(type==SN_CLASS_LABEL_BMP)
		{
			SnLabelBitmap* ret=new SnLabelBitmap();
			ret->setFontName(relative);
			ret->setObjectName(filename.c_str());
			return ret;
		
		}
		else 
		{
			return SnGlobal::identifyFactory()->newInstanceFromUrl(root);
		}
		return NULL;
	}
}


