#ifndef _SN_PROJECT_H_
#define _SN_PROJECT_H_ 


#include <string>
#include <vector>
#include "core/SnIdentify.h"
#include "core/SnEntity2D.h"
#include "core/SnLayer2D.h"

#include "mgr/FsTextureMgr.h"
#include "mgr/FsFelisScriptMgr.h"
#include "mgr/FsFontBitmapMgr.h"
#include "mgr/FsFontTTFMgr.h"
#include "mgr/FsProgramSourceMgr.h"
#include "mgr/FsSprite2DDataMgr.h"

#include "SnEnums.h"

class SnScene;


class SnProject
{
	public:
		static SnProject* create();
		static SnProject* create(Faeris::FsDict* dict);



	public:
		~SnProject();

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

		/* register global info */
		void unRegisterFsGlobalMgr();
		void registerFsGlobalMgr();

		void loadScene();

		/* save and export */
		Faeris::FsDict* takeSaveFst();
		Faeris::FsDict* takeExportFst();

	public:
		SnScene* getCurScene();

		void setCurrentAndSelectIdentify(SnIdentify* ct,const std::vector<SnIdentify*> select);

	protected:
		bool init();
		bool init(Faeris::FsDict* dict);
		SnProject();

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

		/* resolution */
		int m_resolutionX;
		int m_resolutionY;

		/* Scene Config */
		Faeris::FsDict* m_sceneCfg;

		/* resource Mgr */
		Faeris::TextureMgr* m_textureMgr;
		Faeris::FontTTFMgr* m_fontTTFMgr;
		Faeris::FontBitmapMgr* m_fontBmpMgr;
		Faeris::Sprite2DDataMgr* m_sprite2DMgr;
		Faeris::ProgramSourceMgr* m_programSourceMgr;
		Faeris::FelisScriptMgr* m_felisScriptMgr;
};


#endif


