#ifndef _SN_SCENE_H_
#define _SN_SCENE_H_ 

#include "SnIdentify.h"
#include "stage/FsScene.h"

NS_FS_USE

class SnScene:public Scene 
{
	public:
		void setName(std::string name){m_name=name;}
		std::string getName(){return m_name;}

	private:
		std::string m_name;
};



#endif /*_SN_SCENE_H_*/
