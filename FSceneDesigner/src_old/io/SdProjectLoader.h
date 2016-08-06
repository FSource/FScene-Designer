#ifndef _SD_PROJECT_LOADER_H_
#define _SD_PROJECT_LOADER_H_

#include <string>
#include "support/util/FsDict.h"
NS_FS_USE



class SdProject;
class SdSprite;
class SdAnimation;

class SdTimeLine;

class SdProjectLoader 
{
	public:
		SdProjectLoader();
		~SdProjectLoader();

	public:
		SdProject* loadProject(const std::string& filename);

	protected:
		/*  parse  data */
		SdProject* parseProject(FsDict* dict);
		SdSprite* parseSprite(FsDict* dict);


	private:
		SdProject* m_curProject;
};



#endif /*_SD_PROJECT_LOADER_H_*/

