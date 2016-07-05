#ifndef _SD_FSB_EXPORTOR_H_
#define _SD_FSB_EXPORTOR_H_

class SdFsbExporter 
{
	public:
		SdFsbExporter();
		~SdFsbExporter();
	public:
		bool exportSprite(const std::string& filename,SdSprite* sprite);
};

#endif /*_SD_FSB_EXPORTOR_H_*/



