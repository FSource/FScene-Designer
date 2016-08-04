#ifndef _SN_LAYER2D_H_
#define _SN_LAYER2D_H_
#include "stage/layer/FsLayer2D.h"
#include "SnIdentify.h"




class SnLayer2D:public SnIdentify, public Faeris::Layer2D 
{
	public:
		static SnLayer2D* newInstance(Faeris::FsDict* dict);

	public:
		SnLayer2D();
		~SnLayer2D();

public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		
		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);


		virtual void addIdentifyChild(SnIdentify* idenfy);
		virtual void removeIdentifyChild(SnIdentify* idenfy);
		virtual void clearIdentifyChild();


		virtual bool isDragEnabled();
		virtual bool isDropEnabled();
		
		virtual std::vector<SnIdentify*> getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse);
		virtual SnIdentify* getChildHitPoint(Faeris::Vector2f p,bool traverse);
	

	private:
		Faeris::FsArray* m_array;
};


#endif /*_SN_LAYER2D_H_*/
