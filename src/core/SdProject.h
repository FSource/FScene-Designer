#ifndef _SD_PROJECT_H_
#define _SD_PROJECT_H_

#include <string>
#include <vector>

class SdSprite;

class SdHistoryStates;
class SdImageMgr;
class SdIconMgr;

class SdProject 
{
	public:
		static SdProject* create(const std::string& filename);

	public:
		SdProject(const std::string& filename);
		~SdProject();

	public:
		std::string getName();

		SdSprite* createSprite(const std::string& name);
		void removeSprite(SdSprite* sprite);
		void addSprite(int pos,SdSprite* sprite);
		void addSprite(SdSprite* sprite);


		int getSpriteNu();
		SdSprite* getSprite(int index);

		bool hasSpriteWithName(const std::string& name);
		bool hasSprite(SdSprite* sprite);

		int getSpritePos(SdSprite* sprite);

		SdSprite* getCurSprite();
		void setCurSprite(SdSprite* sprite);

		/* resource dir */
		void setResourceDir(const std::string& dir);
		std::string getResourceDir();

		SdImageMgr* getImageMgr();
		SdIconMgr* getIconMgr();



	public:
		bool canRedo();
		bool canUndo();
		bool Redo();
		bool Undo();

	protected:
		void init(const std::string& name);

    private:

        std::vector<SdSprite*> m_sprites;

        SdSprite* m_curSprite;

        std::string m_projectName;
        std::string m_projectDir;
        std::string m_resourceDir;

		SdHistoryStates* m_historyStates;
		SdImageMgr* m_imageMgr;
		SdIconMgr* m_iconMgr;

};

#endif /*_SD_PROJECT_H_*/

















