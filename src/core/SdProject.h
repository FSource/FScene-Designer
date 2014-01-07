#ifndef _SD_PROJECT_H_
#define _SD_PROJECT_H_

class SdSprite;

class SdHistoryStates;
class SdImageMgr;
class SdIconMgr;

class SdProject 
{
	public:
		static SdProject* create(const std::string& dir,const std::string& name);

	public:
		SdProject(const std::string& dir,const std::string& name);
		~SdProject();

	public:
		std::string getName();

		SdSprite* createSprite(const char* name);
		void removeSprite(SdSprite* sprite);

		int getSpriteNu();
		bool hasSpriteWithName(const char* name);
		bool hasSprite(SdSprite* sprite);

		int spritePos(SdSprite* sprite);

		SdSprite* getCurSprite();
		void setCurSprite(SdSprite* sprite);


	public:

		bool canRedo();
		bool canUndo();

	private:
		std::vector<SdSprite*> m_sprites;

		std::string m_projectName;
		std::string m_projectDir;

		std::string m_resourceDir;

		SdHistoryStates* m_historyStates;
		SdImageMgr* m_imageMgr;
		SdIconMgr* m_iconMgr;

};

#endif /*_SD_PROJECT_H_*/

















