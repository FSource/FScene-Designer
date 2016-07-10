#ifndef _SN_LAYER2D_H_
#define _SN_LAYER2D_H_
#include "stage/layer/FsLayer2D.h"
#include "SnIdentify.h"




class SnLayer2D:public SnIdentify, public Faeris::Layer2D 
{
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

		virtual bool isDragEnabled();
		virtual bool isDropEnabled();
		
	


	public:
		void add(Faeris::Entity* entity) FS_OVERRIDE;
		void remove(Faeris::Entity* entity) FS_OVERRIDE;
		void clearEntity() FS_OVERRIDE;

	
		

	public:
		int getEntityNu();
		Faeris::Entity2D * getEntity(int index);
		int getEntityIndex(Faeris::Entity* en);
		

	private:
		Faeris::FsArray* m_array;
};


#endif /*_SN_LAYER2D_H_*/
