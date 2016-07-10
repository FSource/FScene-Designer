#ifndef _SN_PROJECT_H_
#define _SN_PROJECT_H_ 


#include <string>
#include <vector>
#include "core/SnIdentify.h"
#include "core/SnEntity2D.h"
#include "core/SnLayer2D.h"

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


	public:
		SnScene* getCurScene();
		void setCurLayer(SnLayer2D* layer);
		SnLayer2D* getCurLayer();

		void setCurEntity(Faeris::Entity2D* en);
		Faeris::Entity2D* getCurEntity();


	private:
		std::string m_fileName;
		std::string m_dirName;
		std::string m_name;

		SnScene* m_scene;

		SnLayer2D* m_curlayer;

		Faeris::Entity2D* m_curEntity;
		Faeris::FsArray* m_selectEntity;

};


#endif
