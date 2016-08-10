#ifndef _SN_T_ENTITY2D_INL_
#define _SN_T_ENTITY2D_INL_ 

#include "SnGlobal.h"
#include "SnIdentifyFactory.h"


template<typename T> 
TSnEntity2D<T>::TSnEntity2D()
{
	m_array=Faeris::FsArray::create();
	m_className=T::getClassName();
}

template<typename T> 
TSnEntity2D<T>::~TSnEntity2D()
{
	m_array->destroy();
}


template<typename T> 
int TSnEntity2D<T>::identifyType()
{
	return 	SN_CLASS_T_ENTITY2D;
}

template<typename T>
const char* TSnEntity2D<T>::identifyTypeName()
{
	return "TSnEntity2D";
}

template<typename T>
SnIdentify* TSnEntity2D<T>::getIdentifyParent()
{
	Faeris::Entity* ep=T::getParent();
	Faeris::Layer* ly=T::getLayer();
	if(ep==NULL)
	{
		return dynamic_cast<SnIdentify*>(ly);

	}
	return dynamic_cast<SnIdentify*>(ep);
}

template<typename T>
void TSnEntity2D<T>::addIdentifyChild(SnIdentify* identify)
{
	Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>(identify);
	T::addChild(en);
	m_array->push(en);
}

template<typename T>
void TSnEntity2D<T>::removeIdentifyChild(SnIdentify* identify)
{
	Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>(identify);
	T::removeChild(en);
	m_array->remove(en);
}

template<typename T>
void TSnEntity2D<T>::clearIdentifyChild()
{
	m_array->clear();
	T::clearChild();
}

template<typename T>
bool TSnEntity2D<T>::acceptChild(SnIdentify* id)
{
	Entity2D* en =dynamic_cast<Entity2D*>(id);
	if(en==NULL)
	{
		return false;
	}

	return true;
}




template<typename T>
int TSnEntity2D<T>::getIdentifyChildNu()
{
	return m_array->size();
}

template<typename T>
SnIdentify* TSnEntity2D<T>::getIdentifyChild(int index)
{
	Faeris::Entity2D* en=(Faeris::Entity2D*)m_array->get(index);
	return dynamic_cast<SnIdentify*>(en);
}

template<typename T>
int TSnEntity2D<T>::getIdentifyChildIndex(SnIdentify* id)
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

template<typename T>
std::vector<SnIdentify*> TSnEntity2D<T>::getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse)
{
	std::vector<SnIdentify* > ret;
	int child_nu=getIdentifyChildNu();

	for(int i=0;i<child_nu;i++)
	{
		SnIdentify* id=getIdentifyChild(i);
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

template<typename T>
SnIdentify* TSnEntity2D<T>::getChildHitPoint(Faeris::Vector2f point,bool traverse)
{
	int child_nu=getIdentifyChildNu();
	for(int i=child_nu-1;i>=0;i--)
	{
		SnIdentify* id=getIdentifyChild(i);
		if(traverse)
		{
			SnIdentify* ret= id->getChildHitPoint(point,traverse);
			if(ret)
			{
				return ret;
			}
		}
		if(SnUtil::identifyHitPoint(id,point))
		{
			return id;
		}
	}
	return NULL;
}

template<typename T> 
void TSnEntity2D<T>::rotate(float angle)
{
	float r=getRotateZ();
	r+=angle;
	setRotateZ(r);
}

template<typename T> 
Faeris::Vector3f TSnEntity2D<T>::getPositionInWorld()
{
	return T::getPositionInWorld();
}

template<typename T> 
void TSnEntity2D<T>::translateInWorld(float x,float y)
{
	Faeris::Vector3f pos=T::getPositionInWorld();
	Faeris::Vector3f ret=Faeris::Vector3f(pos.x+x,pos.y+y,0);
	setPositionInWorld(ret);
}

template<typename T> 
void TSnEntity2D<T>::translateXInWorld(float x,float y)
{
	Faeris::Matrix4 mat=*getWorldMatrix();
	mat.setScale(Faeris::Vector3(1,1,1));

	Faeris::Vector3f v_x=mat.getColumnX();
	Faeris::Vector3f v_y=mat.getColumnY();

	Faeris::Vector3f m(x,y,0);

	Faeris::Vector3f t=m.proj(v_x);
	translateInWorld(t.x,t.y);
}
template<typename T> 
void TSnEntity2D<T>::translateYInWorld(float x,float y)
{
	Faeris::Matrix4 mat=*getWorldMatrix();
	mat.setScale(Faeris::Vector3(1,1,1));

	Faeris::Vector3f v_x=mat.getColumnX();
	Faeris::Vector3f v_y=mat.getColumnY();

	Faeris::Vector3f m(x,y,0);

	Faeris::Vector3f t=m.proj(v_y);
	translateInWorld(t.x,t.y);
}

template<typename T> 
Faeris::Vector2f TSnEntity2D<T>::toXAxisProj(Faeris::Vector2f v)
{
	Faeris::Matrix4 mat=*getWorldMatrix();
	mat.setScale(Faeris::Vector3(1,1,1));
	Faeris::Vector3f v_x=mat.getColumnX();
	Faeris::Vector3f m(v.x,v.y,0);
	Faeris::Vector3f t=m.proj(v_x);

	return Faeris::Vector2f(t.x,t.y);
}


template<typename T> 
Faeris::Vector2f TSnEntity2D<T>::toYAxisProj(Faeris::Vector2f v)
{
	Faeris::Matrix4 mat=*getWorldMatrix();
	mat.setScale(Faeris::Vector3(1,1,1));
	Faeris::Vector3f v_y=mat.getColumnY();
	Faeris::Vector3f m(v.x,v.y,0);
	Faeris::Vector3f t=m.proj(v_y);

	return Faeris::Vector2f(t.x,t.y);
}

template<typename T>
void TSnEntity2D<T>::getBoundSize2D(float* minx,float* maxx,float* miny,float* maxy)
{
	return T::getBoundSize2D(minx,maxx,miny,maxy);
}

template<typename T>
SnAttrGroupList* TSnEntity2D<T>:: getAttributeList()
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


inline void TSnEntity2D_setChildren(Faeris::FsObject* ob,Faeris::FsArray* attr)
{
	SnIdentify* en_id=dynamic_cast<SnIdentify*>(ob);
	int size=attr->size();
	for(int i=0;i<size;i++)
	{
		Faeris::FsDict* dict=attr->getDict(i);
		if(dict)
		{
			SnIdentify* id=SnGlobal::identifyFactory()->newInstance(dict);
			if(id)
			{
				Faeris::Entity2D* ch=dynamic_cast<Faeris::Entity2D*>(id);
				if(ch)
				{
					en_id->addIdentifyChild(id);
				}
				else 
				{
					FS_TRACE_WARN("Not SubClass Of Entity2D,Ingore Item(%d)",i);
					delete id;
				}
			}
		}
		else 
		{
			FS_TRACE_WARN("Not Dict,Ingore Item(%d)",i);
		}
	}
}

inline Faeris::FsArray* TSnEntity2D_getChildren(Faeris::FsObject* ob)
{
	SnIdentify* id=dynamic_cast<SnIdentify*>(ob);

	Faeris::FsArray* ret= Faeris::FsArray::create();
	int child_nu=id->getIdentifyChildNu();
	for(int i=0;i<child_nu;i++)
	{
		SnIdentify* ch=id->getIdentifyChild(i);
		Faeris::FsDict* dict=ch->takeObjectFst();
		ret->push(dict);
	}
	return ret;
}






	template<typename T>
std::vector<std::string> TSnEntity2D<T>::getObjectFstAttrList()
{
	std::vector<std::string> ret= SnIdentify::getObjectFstAttrList();
	ret.push_back("position");
	ret.push_back("scale");
	ret.push_back("rotateZ");
	ret.push_back("visible");
	ret.push_back("visibles");
	ret.push_back("anchor");
	ret.push_back("size");
	ret.push_back("touchEnabled");
	ret.push_back("touchesEnabled");
	ret.push_back("touchDispatchEnabled");
	ret.push_back("touchesDispatchEnabled");
	ret.push_back("color");
	ret.push_back("opacity");
	ret.push_back("blendEquation");
	ret.push_back("blendSrc");
	ret.push_back("blendDst");
	return ret;
}




#endif /*_SN_T_ENTITY2D_INL_*/
