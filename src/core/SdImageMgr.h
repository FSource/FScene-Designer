#ifndef _SD_IMAGE_MGR_H_
#define _SD_IMAGE_MGR_H_ 

class SdImage;

class SdImageMgr 
{
	public:
		SdImageMgr(const std::string& dir);
		~SdImageMgr();

	public:
		void setResourceDir(const std::string& dir);
		void refresh();
		SdImage* load(const std::string& name);
};

#endif /*_SD_IMAGE_MGR_H_*/

