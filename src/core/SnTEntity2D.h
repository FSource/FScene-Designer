#ifndef _SN_T_ENTITY2D_H_
#define _SN_T_ENTITY2D_H_ 

#include "stage/entity/FsEntity2D.h"
#include "stage/layer/FsLayer.h"
#include "core/SnIdentify.h"


template<class T>
class TSnEntity2D:public SnIdentify ,public T
{
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

		virtual int getIdentifyChildNu()
		{
                        return T::getChildNu();
		}

		virtual SnIdentify* getIdentifyChild(int index)
		{
                        Faeris::Entity* en=T::getChild(index);
			return dynamic_cast<SnIdentify*>(en);
		}
		virtual int getIdentifyChildIndex(SnIdentify* /*id*/)
		{
			//Faeris::Entity* en=dynamic_cast<Faeris::Entity*>(id);
			return 0;
		}

		virtual bool isDragEnabled(){return true;}
		virtual bool isDropEnabled(){return true;}

};


#endif /*_SN_ENTITY2D_H_*/
