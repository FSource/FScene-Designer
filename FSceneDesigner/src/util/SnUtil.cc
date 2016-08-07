#include "util/SnUtil.h"
#include "core/SnIdentify.h"

#include "stage/entity/FsEntity2D.h"


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
	QString toRelativePath(const QString& root,const QString& path)
	{
		QString rel_root=root+"/";
		assert(path.startsWith(rel_root));
		QString ret=path;
		ret.remove(0,rel_root.size());
		return ret;
	}
	*/



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
}


