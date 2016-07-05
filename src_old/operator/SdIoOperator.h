#ifndef _SD_IO_OPERATOR_H_
#define _SD_IO_OPERATOR_H_

class SdProject;

class SdIoOperator
{
	public:
		SdIoOperator();
		~SdIoOperator();

	public:
		SdProject* loadProject(const std::string& filename);
		bool saveProject(const std::string& filename,SdProject* proj);

		bool exportSpriteFst(const std::string& filename,SdSprite* sprite);
		bool exportSpriteFsb(const std::string& filename,SdSprite* sprite);
		bool exportSpriteJson(const std::string& filename,SdSprite* sprite);
		bool exportSpriteXml(const std::string& filename,SdSprite* sprite);

};



#endif /*_SD_IO_OPERATOR_H_*/

