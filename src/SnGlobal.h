#ifndef _SN_GLOBAL_H_
#define _SN_GLOBAL_H_

class SnProject;
class SnMainWindow;
class SnMsgCenter;
class SnGlobal
{
	public:
		static void moduleInit();
		static void moduleExit();


	public:
		static SnProject* getProject();
		static void setProject(SnProject* proj);



		static void setMainWindow(SnMainWindow* win);
		static SnMainWindow* getMainWindow();


	private:
		static SnProject* m_project;
		static SnMsgCenter* m_msgCenter;
		static SnMainWindow* m_mainWindow;
};





#endif /*_SN_GLOBAL_H_*/
