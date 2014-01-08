#ifndef _SD_PROJECT_WIRTER_H_
#define _SD_PROJECT_WIRTER_H_


#include <string>

#include "sys/io/FsSysFile.h"
NS_FS_USE

#include "core/SdSubTimeLine.h"
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
        bool writeAnimation(FsFile* file,const std::string& prefix,SdAnimation* anim);
		bool writeTimeLine(FsFile* file,const std::string& prefix,SdTimeLine* timeline);
		bool writeScaleTimeLine(FsFile* file,const std::string& prefix,SdScaleTimeLine* timeline);
		bool writeTranslateTimeLine(FsFile* file,const std::string& prefix,SdTranslateTimeLine* timeline);
		bool writeRotateTimeLine(FsFile* file,const std::string& prefix,SdRotateTimeLine* timeline);
		bool writeColorTimeLine(FsFile* file,const std::string& prefix,SdColorTimeLine* timeline);
        bool writeOtherTimeLine(FsFile* file,const std::string& prefix,SdOtherTimeLine* timeline);
        bool writeAbout(FsFile* file,const std::string& prefix,SdProject* proj);
};

#endif /*_SD_PROJECT_WIRTER_H_*/


