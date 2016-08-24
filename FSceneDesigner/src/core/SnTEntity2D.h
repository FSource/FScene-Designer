#ifndef _SN_T_ENTITY2D_H_
#define _SN_T_ENTITY2D_H_ 

#include "stage/entity/FsEntity2D.h"
#include "stage/layer/FsLayer.h"
#include "core/SnIdentify.h"
#include "FsObject.h"
#include "FsEnums.h"
#include "util/SnUtil.h"
#include "support/util/FsDict.h"

template<class T>
class TSnEntity2D:public SnIdentify ,public T
{
		
	public:
		TSnEntity2D();
		virtual ~TSnEntity2D();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnIdentify* getIdentifyParent();
		virtual void addIdentifyChild(SnIdentify* identify);
		virtual void removeIdentifyChild(SnIdentify* identify);
		virtual void clearIdentifyChild();
		virtual bool acceptChild(SnIdentify* identify);


		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

		virtual std::vector<SnIdentify*> getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse);


		virtual SnIdentify* getChildHitPoint(Faeris::Vector2f point,bool traverse);
		virtual void rotate(float angle);
		virtual Faeris::Vector3f getPositionInWorld();
		virtual void translateInWorld(float x,float y);

		virtual void translateXInWorld(float x,float y);
		virtual void translateYInWorld(float x,float y);

		virtual Faeris::Vector2f toXAxisProj(Faeris::Vector2f v);
		virtual Faeris::Vector2f toYAxisProj(Faeris::Vector2f v);

		virtual void getBoundSize2D(float* minx,float* maxx,float* miny,float* maxy);



		virtual bool isDragEnabled(){return true;}
		virtual bool isDropEnabled(){return true;}

		virtual SnAttrGroupList* getAttributeList();

		virtual std::vector<std::string> getObjectFstAttrList();
		virtual bool filterExportValue(const char* name,const Faeris::FsVariant& value);

	private:
		Faeris::FsArray* m_array;

};


#include "SnTEntity2D.inl"


#endif /*_SN_ENTITY2D_H_*/
