#ifndef _SN_SCENE_H_
#define _SN_SCENE_H_ 


#include "stage/FsScene.h"
#include "support/util/FsArray.h"
#include "SnIdentify.h"


class SnScene:public SnIdentify,public Faeris::Scene
{
	public:
		FS_CLASS_DECLARE(SnScene);

	public:
		static SnScene* newInstance(Faeris::FsDict* dict);


	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnAttrGroupList* getAttributeList();
		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);


		virtual void addIdentifyChild(SnIdentify* idenfy);
		virtual void removeIdentifyChild(SnIdentify* idenfy);
		virtual void clearIdentifyChild();


		virtual std::vector<std::string> getObjectFstAttrList();
	
	public:
		SnScene();

};



#endif /*_SN_SCENE_H_*/
