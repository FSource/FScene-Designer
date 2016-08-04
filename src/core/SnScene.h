#ifndef _SN_SCENE_H_
#define _SN_SCENE_H_ 


#include "stage/FsScene.h"
#include "support/util/FsArray.h"
#include "SnIdentify.h"


class SnScene:public SnIdentify,public Faeris::Scene
{
	public:
		static SnScene* newInstance(Faeris::FsDict* dict);

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnAttrGroupList* getAttributeList();
		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);


	private:
		std::string m_name;
};



#endif /*_SN_SCENE_H_*/
