#ifndef _SN_PROJECT_H_
#define _SN_PROJECT_H_ 


#include <string>
#include <vector>
#include "core/SnIdentify.h"

class SnScene;

class SnProject:public SnIdentify
{
	public:
		SnProject();
		~SnProject();

	public:
		int identifyType();
		const char* identifyName();

	public:
		std::string getFileName(){return m_fileName;}

		void setFileName(std::string name){m_fileName=name;}

		std::string getDirName(){return m_dirName;}
		void setDirName(std::string name){m_dirName=name;}

		void setName(std::string name);
		std::string getName(){return m_name;}

		SnScene* getCurScene();

	private:
		std::string m_fileName;
		std::string m_dirName;
		std::string m_name;

		SnScene* m_scene;

};


#endif
