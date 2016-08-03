#ifndef _SN_PROJECT_H_
#define _SN_PROJECT_H_ 


#include <string>
#include <vector>
#include "core/SnIdentify.h"
#include "core/SnEntity2D.h"
#include "core/SnLayer2D.h"

#include "SnEnums.h"

class SnScene;


class SnProject:public SnIdentify
{
	public:
		SnProject();
		SnProject(Faeris::FsDict* dict);

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

		SnIdentify* getCurrentIdentify(){return m_currentIdentify;}
		std::vector<SnIdentify*> getSelectedIdentify(){return m_selectIdentifys;}
		std::vector<SnIdentify*> getSelectedIdentifyRoot(){return m_selectIdentifysRoots;}


		SnLayer2D* getCurrentLayer(){return m_currentLayer;}

		/* edit mode */
		void setEditMode(SN_EditMode mode){m_editMode=mode;}
		SN_EditMode getEditMode(){return m_editMode;}

		void setTranslateMode(SN_TranslateMode mode){m_translateMode=mode;}
		SN_TranslateMode getTranslateMode(){return m_translateMode;}

	public:
		SnScene* getCurScene();

		void setCurrentAndSelectIdentify(SnIdentify* ct,const std::vector<SnIdentify*> select);


	private:
		std::string m_fileName;
		std::string m_dirName;
		std::string m_name;

		SnScene* m_scene;

		SnIdentify* m_currentIdentify;
		std::vector<SnIdentify*> m_selectIdentifys;
		std::vector<SnIdentify*> m_selectIdentifysRoots;
		SnLayer2D* m_currentLayer;

		/* edit mode */
		SN_EditMode m_editMode;
		SN_TranslateMode m_translateMode;
};

#endif


