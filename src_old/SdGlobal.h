#ifndef _SD_GLOBAL_H_
#define _SD_GLOBAL_H_

class SdProject;
class SdSprite;
class SdAnimation;
class SdMsgCenter;
class SdMainWindow;

class SdGlobal 
{
	public:
		static void moduleInit();
		static void moduleExit();

	public:
		static SdProject* getProject();
		static void setProject(SdProject* proj);

		static SdSprite* getCurSprite();
		static void setCurSprite(SdSprite* sprite);

		static SdAnimation* getCurAnimation();
		static void setCurAnimation(SdAnimation* anim);


		static SdMsgCenter* getMsgCenter();
		static void setMsgCenter(SdMsgCenter* msg_center);

		static void setMainWindow(SdMainWindow* win);
		static SdMainWindow* getMainWindow();


		/* undo/redo */
		static bool canUndo();
		static bool canRedo(); 

	private:
		static SdProject* m_project;
		static SdMsgCenter* m_msgCenter;
		static SdMainWindow* m_mainWindow;
};

#endif /*_SD_GLOBAL_H_*/


