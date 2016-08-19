

#include "SnScene.h"
#include "core/SnEntity2D.h"
#include "core/SnProject.h"
#include "support/util/FsScriptUtil.h"
#include "SnGlobal.h"
#include "SnIdentifyFactory.h"
#include "FsGlobal.h"
#include "sys/io/FsVFS.h"


NS_FS_USE

SnProject* SnProject::create()
{
	SnProject* proj=new SnProject();
	proj->init();
	return proj;


}

SnProject* SnProject::create(FsDict* dict)
{
	SnProject* proj=new SnProject();
	bool ret=proj->init(dict);
	if(!ret)
	{
		delete proj;
		return NULL;
	}

	return proj;

}


SnProject::SnProject()
{
	m_sceneCfg=NULL;
	m_scene=NULL;

	m_currentIdentify=NULL;
	m_currentLayer=NULL;

	m_editMode=SN_EditMode::TRANSALTE;
	m_translateMode=SN_TranslateMode::LOCAL;

	m_resolutionX=0;
	m_resolutionY=0;

	m_textureMgr= TextureMgr::create();
	FS_NO_REF_DESTROY(m_textureMgr);

	m_fontTTFMgr= FontTTFMgr::create();
	FS_NO_REF_DESTROY(m_fontTTFMgr);

	m_fontBmpMgr= FontBitmapMgr::create();
	FS_NO_REF_DESTROY(m_fontBmpMgr);

	m_sprite2DMgr=Sprite2DDataMgr::create();
	FS_NO_REF_DESTROY(m_sprite2DMgr);

	m_programSourceMgr=ProgramSourceMgr::create();
	m_programSourceMgr->loadPreDefineShader();
	FS_NO_REF_DESTROY(m_programSourceMgr);

	m_felisScriptMgr= FelisScriptMgr::create();
	FS_NO_REF_DESTROY(m_felisScriptMgr);

}



SnProject::~SnProject()
{
	if(m_scene)
	{
		delete m_scene;
	}

	if(m_sceneCfg)
	{
		m_sceneCfg->decRef();
	}

	m_textureMgr->destroy();
	m_fontBmpMgr->destroy();
	m_fontTTFMgr->destroy();
	m_sprite2DMgr->destroy();
	m_programSourceMgr->destroy();
	m_felisScriptMgr->destroy();

}

bool SnProject::init()
{
	return true;
}

bool SnProject::init(Faeris::FsDict* dict)
{
	FsString* type_name=dict->lookupString("projectType");
	if(type_name==NULL)
	{
		return false;
	}

	if(!type_name->equal("FSceneDesigner"))
	{
		return false;
	}

	ScriptUtil::getInteger(dict,"resolutionX",&m_resolutionX);
	ScriptUtil::getInteger(dict,"resolutionY",&m_resolutionY);
	m_sceneCfg=dict->lookupDict("scene");
	return true;
}


void SnProject::loadScene()
{
	if(m_sceneCfg==NULL)
	{
		m_scene=new SnScene();
		m_scene->setIdentifyName(m_name.c_str());
	}
	else 
	{
		SnIdentify* id=SnGlobal::identifyFactory()->newInstance(m_sceneCfg);

		SnScene* scene=dynamic_cast<SnScene*>(id);
		if(!scene)
		{
			m_scene=new SnScene();
			m_scene->setIdentifyName(m_name.c_str());
			return ;
		}
		m_scene=scene;
	}

}



FsDict* SnProject::takeSaveFst()
{
	if(m_scene==NULL)
	{
		return NULL;
	}

	FsDict* ret=FsDict::create();
	ret->insert(FsString::create("projectType"),FsString::create("FSceneDesigner"));
	ret->insert(FsString::create("version"),FsString::create("v2.0.0"));

	char buf[128];
	sprintf(buf,"%d",m_resolutionX);
	ret->insert(FsString::create("resolutionX"),FsString::create(buf));

	sprintf(buf,"%d",m_resolutionY);
	ret->insert(FsString::create("resolutionY"),FsString::create(buf));


	ret->insert(FsString::create("scene"),m_scene->takeObjectFst());

	ret->insert(FsString::create("about"),FsString::create("FsScene Designer For FEngine"));
	ret->insert(FsString::create("email"),FsString::create("fscene@fsource.cn"));
	ret->insert(FsString::create("url"),FsString::create("fscene.fsource.cn"));
	return ret;
}

FsDict* SnProject::takeExportFst()
{
	if(m_scene==NULL)
	{
		return NULL;
	}
	return m_scene->takeObjectFst();
}



void SnProject::setName(std::string name)
{
	m_name=name;
}



SnScene* SnProject::getCurScene()
{
	return m_scene;
}


void SnProject::setCurrentAndSelectIdentify(SnIdentify* ct,const std::vector<SnIdentify*> select)
{
	if(ct!=NULL)
	{
		if(dynamic_cast<SnScene*>(ct))
		{
			m_currentLayer=NULL;
		}
		else if(dynamic_cast<SnLayer2D*>(ct))
		{
			m_currentLayer=dynamic_cast<SnLayer2D*>(ct);
		}
		else if(dynamic_cast<Entity2D*>(ct))
		{
			Entity2D* en=dynamic_cast<Entity2D*>(ct);
			Layer2D* l=(Layer2D*)en->getLayer();
			m_currentLayer=dynamic_cast<SnLayer2D*>(l);
		}
	}


	m_currentIdentify=ct;
	m_selectIdentifys=select;

	m_selectIdentifysRoots.clear();

	int size=m_selectIdentifys.size();

	for(int i=0;i<size;i++)
	{
		SnIdentify* id=m_selectIdentifys[i];

		bool push_back=true;
		for(int j=0;j<size;j++)
		{
			if(id->isAncestors(m_selectIdentifys[j]))
			{

				push_back=false;
			}
		}
		if(push_back)
		{
			m_selectIdentifysRoots.push_back(id);
		}
	}
}


void SnProject::unRegisterFsGlobalMgr()
{
	Global::setTextureMgr(NULL);
	Global::setFontTTFMgr(NULL);

	Global::setFontBitmapMgr(NULL);
	Global::setSprite2DDataMgr(NULL);
	Global::setProgramSourceMgr(NULL);
	Global::setFelisScriptMgr(NULL);

}


void SnProject::registerFsGlobalMgr()
{
	Global::setTextureMgr(m_textureMgr);
	Global::setFontTTFMgr(m_fontTTFMgr);

	Global::setSprite2DDataMgr(m_sprite2DMgr);
	Global::setProgramSourceMgr(m_programSourceMgr);
	Global::setFelisScriptMgr(m_felisScriptMgr);
	Global::setFontBitmapMgr(m_fontBmpMgr);

	VFS::setRoot(m_dirName.c_str());
}













