#ifndef _SN_T_ENTITY2D_H_
#define _SN_T_ENTITY2D_H_ 

#include "stage/entity/FsEntity2D.h"
#include "stage/layer/FsLayer.h"
#include "core/SnIdentify.h"
#include "FsObject.h"
#include "FsEnums.h"
#include "util/SnUtil.h"

template<class T>
class TSnEntity2D:public SnIdentify ,public T
{
	public:
		TSnEntity2D()
		{
			m_array=Faeris::FsArray::create();
		}
		virtual ~TSnEntity2D()
		{
			m_array->destroy();
		}
	public:
		virtual int identifyType()
		{
			return 	SN_CLASS_T_ENTITY2D;
		}

		virtual const char* identifyTypeName()
		{
			return "TSnEntity2D";
		}

		virtual SnIdentify* getIdentifyParent()
		{
			Faeris::Entity* ep=T::getParent();
			Faeris::Layer* ly=T::getLayer();
			if(ep==NULL)
			{
				return dynamic_cast<SnIdentify*>(ly);

			}
			return dynamic_cast<SnIdentify*>(ep);

		}
		virtual void addIdentifyChild(SnIdentify* identify)
		{
			Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>(identify);

			T::addChild(en);
			m_array->push(en);
		}

		virtual void removeIdentifyChild(SnIdentify* identify)
		{
			Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>(identify);

			T::removeChild(en);
			m_array->remove(en);
		}

		virtual void clearIdentifyChild()
		{
			m_array->clear();
			T::clearChild();
		}



		virtual int getIdentifyChildNu()
		{
			return m_array->size();
		}

		virtual SnIdentify* getIdentifyChild(int index)
		{
			Faeris::Entity2D* en=(Faeris::Entity2D*)m_array->get(index);
			return dynamic_cast<SnIdentify*>(en);
		}
		virtual int getIdentifyChildIndex(SnIdentify* id)
		{
			Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>(id);
			int size=m_array->size();
			for(int i=0;i<size;i++)
			{
				if(en==m_array->get(i))
				{
					return i;
				}
			}

			return 0;
		}

		virtual std::vector<SnIdentify*> getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse)
		{
			std::vector<SnIdentify* > ret;
			int size=m_array->size();
			for(int i=0;i<size;i++)
			{
				Entity2D* en=(Entity2D*)m_array->get(i);
				SnIdentify* id=dynamic_cast<SnIdentify*>(en);
				if(SnUtil::identifyInRect(id,start,end))
				{
					ret.push_back(id);
				}

				if(traverse)
				{
					std::vector<SnIdentify*> r=id->getChildInArea(start,end,traverse);
					ret.insert(ret.end(),r.begin(),r.end());
				}
			}

			return ret;
		}

		virtual SnIdentify* getChildHitPoint(Faeris::Vector2f point,bool traverse)
		{
			int size=m_array->size();
			for(int i=size-1;i>=0;i--)
			{
				Entity2D* en=(Entity2D*)m_array->get(i);
				SnIdentify* id=dynamic_cast<SnIdentify*>(en);
				if(SnUtil::identifyHitPoint(id,point))
				{
					return id;
				}

				if(traverse)
				{
					SnIdentify* ret= id->getChildHitPoint(point,traverse);
					if(ret)
					{
						return ret;
					}
				}
			}
			return NULL;

		}
		virtual void rotate(float angle)
		{
			float r=getRotateZ();
			r+=angle;
			setRotateZ(r);
		}

		virtual Faeris::Vector3f getPositionInWorld()
		{
			return T::getPositionInWorld();
		}

		virtual void translateInWorld(float x,float y)
		{
			Faeris::Vector3f pos=getPositionInWorld();
			Faeris::Vector3f ret=Faeris::Vector3f(pos.x+x,pos.y+y,0);
			setPositionInWorld(ret);
		}

		virtual void translateXInWorld(float x,float y)
		{
			Faeris::Matrix4 mat=*getWorldMatrix();
			mat.setScale(Faeris::Vector3(1,1,1));

			Faeris::Vector3f v_x=mat.getColumnX();
			Faeris::Vector3f v_y=mat.getColumnY();

			Faeris::Vector3f m(x,y,0);

			Faeris::Vector3f t=m.proj(v_x);
			translateInWorld(t.x,t.y);
		}


		virtual void translateYInWorld(float x,float y)
		{
			Faeris::Matrix4 mat=*getWorldMatrix();
			mat.setScale(Faeris::Vector3(1,1,1));

			Faeris::Vector3f v_x=mat.getColumnX();
			Faeris::Vector3f v_y=mat.getColumnY();

			Faeris::Vector3f m(x,y,0);

			Faeris::Vector3f t=m.proj(v_y);
			translateInWorld(t.x,t.y);
		}
		virtual Faeris::Vector2f toXAxisProj(Faeris::Vector2f v)
		{
			Faeris::Matrix4 mat=*getWorldMatrix();
			mat.setScale(Faeris::Vector3(1,1,1));
			Faeris::Vector3f v_x=mat.getColumnX();
			Faeris::Vector3f m(v.x,v.y,0);
			Faeris::Vector3f t=m.proj(v_x);

			return Faeris::Vector2f(t.x,t.y);

		}

		virtual Faeris::Vector2f toYAxisProj(Faeris::Vector2f v)
		{
			Faeris::Matrix4 mat=*getWorldMatrix();
			mat.setScale(Faeris::Vector3(1,1,1));
			Faeris::Vector3f v_y=mat.getColumnY();
			Faeris::Vector3f m(v.x,v.y,0);
			Faeris::Vector3f t=m.proj(v_y);

			return Faeris::Vector2f(t.x,t.y);
		}

	
		virtual void getBoundSize2D(float* minx,float* maxx,float* miny,float* maxy)
		{
			return T::getBoundSize2D(minx,maxx,miny,maxy);
		}



		virtual bool isDragEnabled(){return true;}
		virtual bool isDropEnabled(){return true;}

		virtual SnAttrGroupList* getAttributeList()
		{
			SnAttrGroupList* glist=SnIdentify::getAttributeList();

			SnAttrGroupDesc* group=new SnAttrGroupDesc("Entity");
			group->addAttrTypeDesc(createAttributeDesc("position",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("scale",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("rotateZ",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("visible",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("visibles",SN_TYPE_NORMAL));

			glist->addAttrGroupDesc(group);


			group=new SnAttrGroupDesc("Entity2D");
			group->addAttrTypeDesc(createAttributeDesc("anchor",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("size",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("touchEnabled",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("touchesEnabled",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("touchDispatchEnabled",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("touchesDispatchEnabled",SN_TYPE_NORMAL));

			glist->addAttrGroupDesc(group);

			group=new SnAttrGroupDesc("Material2D");
			group->addAttrTypeDesc(createAttributeDesc("color",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("opacity",SN_TYPE_NORMAL));

			group->addAttrTypeDesc(createAttributeDesc("blendEquation",Faeris::FsEnum_BlendEquationGetEnumName));
			group->addAttrTypeDesc(createAttributeDesc("blendSrc",Faeris::FsEnum_BlendFactorGetEnumName));
			group->addAttrTypeDesc(createAttributeDesc("blendDst",Faeris::FsEnum_BlendFactorGetEnumName));

			glist->addAttrGroupDesc(group);
			return glist;
		}

	private:
		Faeris::FsArray* m_array;
};


#endif /*_SN_ENTITY2D_H_*/
