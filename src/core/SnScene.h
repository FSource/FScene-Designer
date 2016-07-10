#ifndef _SN_SCENE_H_
#define _SN_SCENE_H_ 


#include "stage/FsScene.h"
#include "SnIdentify.h"


class SnScene:public SnIdentify,public Faeris::Scene
{

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

	private:
		std::string m_name;
};



#endif /*_SN_SCENE_H_*/
