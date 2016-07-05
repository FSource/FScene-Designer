#ifndef _SD_PROJECT_WIRTER_H_
#define _SD_PROJECT_WIRTER_H_


#include <string>

#include "sys/io/FsSysFile.h"
NS_FS_USE


class SdProject;
class SdSprite;
class SdAnimation;
class SdTimeLine;

class SdProjectWriter
{
	public:
		SdProjectWriter();
		~SdProjectWriter();

	public:
		bool saveProject(const std::string& filename,SdProject* proj);

	protected:
		/* write data */
		bool writeProject(FsFile* file,const std::string& prefix, SdProject* proj);
		bool writeSprite(FsFile* file,const std::string& prefix,SdSprite* sprite);

        bool writeAbout(FsFile* file,const std::string& prefix,SdProject* proj);
};

#endif /*_SD_PROJECT_WIRTER_H_*/


