#ifndef _SN_T_ENTITY2D_H_
#define _SN_T_ENTITY2D_H_ 

#include "stage/entity/FsEntity2D.h"
#include "stage/layer/FsLayer.h"
#include "core/SnIdentify.h"
#include "FsObject.h"
#include "FsEnums.h"


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



		virtual bool isDragEnabled(){return true;}
		virtual bool isDropEnabled(){return true;}

		virtual SnAttrGroupList* getAttributeList()
		{
			SnAttrGroupList* glist=SnIdentify::getAttributeList();

			SnAttrGroupDesc* group=new SnAttrGroupDesc("Entity");
			group->addAttrTypeDesc(createAttributeDesc("position",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("scale",SN_TYPE_NORMAL));
			group->addAttrTypeDesc(createAttributeDesc("rotate",SN_TYPE_NORMAL));
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
