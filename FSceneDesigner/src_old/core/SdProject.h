#ifndef _SD_PROJECT_H_
#define _SD_PROJECT_H_

#include <string>
#include <vector>

#include "core/SdIdentify.h"
#include "command/SdHistoryStates.h"


class SdSprite;

class SdImageMgr;
class SdIconMgr;

class SdProject:public SdIdentify 
{
	public:
		static SdProject* create(const std::string& filename);

	public:
		SdProject(const std::string& filename);
		~SdProject();

	public:
		int getClassType();
		const char* className();

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
		SdCommand* redo();
		SdCommand* undo();
		void pushCommand(SdCommand* cmd);

	protected:
		void init(const std::string& name);

    private:

        std::vector<SdSprite*> m_sprites;

        SdSprite* m_curSprite;

        std::string m_projectName;
        std::string m_projectDir;
        std::string m_resourceDir;

		SdImageMgr* m_imageMgr;
		SdIconMgr* m_iconMgr;

		SdHistoryStates m_historyStates;
};

#endif /*_SD_PROJECT_H_*/

















