#ifndef _SD_GLOBAL_H_
#define _SD_GLOBAL_H_

class SdProject;
class SdMsgCenter;

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

	private:
		static SdProject* m_project;
		static SdMsgCenter* m_msgCenter;
};

#endif /*_SD_GLOBAL_H_*/


