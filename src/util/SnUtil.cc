#include "util/SnUtil.h"
#include "core/SnIdentify.h"

#include "stage/entity/FsEntity2D.h"


NS_FS_USE

namespace  SnUtil 
{
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

		if(e_minx>minx&&e_maxx<maxx&&e_miny>miny&&e_maxy<maxy)
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

	bool hitIdentityCenterPoint(SnIdentify* id,Vector2f pos,float gap)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		Vector3f t= en->worldToLocal(Vector3f(pos.x,pos.y,0));
		if(Math::abs(t.x) < gap)
		{
			if(Math::abs(t.y) < gap)
			{
				return true;
			}
		}

		return false;
	}

	bool hitIdentityAxisX(SnIdentify* id,Vector2f pos,float width,float height)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		Vector3f t= en->worldToLocal(Vector3f(pos.x,pos.y,0));

		if(Math::abs(t.y)< width)
		{
			if(t.x>0&&t.x< height)
			{
				return true;
			}
		}

		return false;
	}

	bool hitIdentityAxisY(SnIdentify* id,Vector2f pos,float width,float height)
	{
		Entity2D* en=dynamic_cast<Entity2D*>(id);
		if(!en)
		{
			return false;
		}

		Vector3f t= en->worldToLocal(Vector3f(pos.x,pos.y,0));
		if(Math::abs(t.x)<width)
		{
			if(t.y>0&&t.y<height)
			{
				return true;
			}
		}
		return false;
	}


}

