#ifndef _SN_SCENE_H_
#define _SN_SCENE_H_ 


#include "stage/FsScene.h"
#include "support/util/FsArray.h"
#include "SnIdentify.h"


class SnScene:public SnIdentify,public Faeris::Scene
{

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);



	private:
		std::string m_name;
		Faeris::FsArray m_array;
};



#endif /*_SN_SCENE_H_*/
