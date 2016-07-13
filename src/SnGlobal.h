#ifndef _SN_GLOBAL_H_
#define _SN_GLOBAL_H_

class SnProject;
class SnMainWindow;
class SnMsgCenter;

class SnDataOperator;
class SnUiOperator;
class SnIoOperator;
class SnScene;

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

	public:
		static SnDataOperator* dataOperator();
		static SnUiOperator* uiOperator();
		static SnIoOperator* ioOperator();
		static SnMsgCenter* msgCenter();


	private:
		static SnProject* m_project;
		static SnMsgCenter* m_msgCenter;
		static SnMainWindow* m_mainWindow;
		static SnDataOperator* m_dataOperator;
		static SnUiOperator* m_uiOperator;
		static SnIoOperator* m_ioOperator;
};






#endif /*_SN_GLOBAL_H_*/
