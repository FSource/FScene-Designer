#ifndef _SD_GLOBAL_H_
#define _SD_GLOBAL_H_

class SdProject;
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

		static SdMsgCenter* getMsgCenter();
		static void setMsgCenter(SdMsgCenter* msg_center);

		static void setMainWindow(SdMainWindow* win);
		static SdMainWindow* getMainWindow();

	private:
		static SdProject* m_project;
		static SdMsgCenter* m_msgCenter;
		static SdMainWindow* m_mainWindow;
};

#endif /*_SD_GLOBAL_H_*/


