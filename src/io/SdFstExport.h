#ifndef _SD_FST_EXPORTER_H_
#define _SD_FST_EXPORTER_H_ 

class SdFstExporter
{
	public:
		SdFstExporter();
		~SdFstExporter();
		
	public:
		bool exportSprite(const std::string& filename,SdSprite* sprite);

	protected:

};

#endif /*_SD_FST_EXPORTER_H_*/

