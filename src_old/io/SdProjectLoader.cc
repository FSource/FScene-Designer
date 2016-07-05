#include "sys/io/FsSysFile.h"
#include "support/util/FsArray.h"
#include "support/util/FsDict.h"
#include "support/util/FsString.h"
#include "support/util/FsScriptUtil.h"
NS_FS_USE

#include "io/SdProjectLoader.h"
#include "core/SdProject.h"
#include "core/SdSprite.h"

SdProjectLoader::SdProjectLoader()
{
	m_curProject=NULL;
}

SdProjectLoader::~SdProjectLoader()
{
}




SdProject* SdProjectLoader::loadProject(const std::string& filename)
{
    FsFile* file=SysFile::create(filename.c_str());
	if(file==NULL)
	{
		return NULL;
	}

	FsDict* file_dict=ScriptUtil::parseScript(file);

	if(file_dict==NULL)
	{
		file->decRef();
		return NULL;
	}

	FsDict* project_dict=ScriptUtil::getDict(file_dict,"project");

	if(project_dict==NULL)
	{
		file->decRef();
		file_dict->decRef();
		return NULL;
	}

	SdProject* proj=parseProject(project_dict);

	file_dict->decRef();
	project_dict->decRef();
	file->decRef();

	return proj;
}


SdProject* SdProjectLoader::parseProject(FsDict* dict)
{
    SdProject* proj=new SdProject("untitle_project");
    FsArray* f_sprites=ScriptUtil::getArray(dict,"sprites");
	if(f_sprites)
	{
		int size=f_sprites->size();
		for(int i=0;i<size;i++)
		{
            FsDict* f_s=ScriptUtil::getDict(f_sprites,i);
			if(f_s)
			{
				SdSprite* sprite=parseSprite(f_s);
				if(sprite)
				{
					proj->addSprite(sprite);
				}
			}
			FS_SAFE_DEC_REF(f_s);
		}
	}
	FS_SAFE_DEC_REF(f_sprites);
	return proj;
}


SdSprite* SdProjectLoader::parseSprite(FsDict* dict)
{

	FsString* f_name=ScriptUtil::getString(dict,"name");
	if(!f_name)
	{
		return NULL;
	}
	SdSprite* sprite=new SdSprite(f_name->cstr());
	FS_SAFE_DEC_REF(f_name);

    FsArray* f_animations=ScriptUtil::getArray(dict,"animations");
	if(f_animations)
	{
		int size=f_animations->size();
		
		for(int i=0;i<size;i++)
		{
			FsDict* f_anim=ScriptUtil::getDict(f_animations,i);
			if(f_anim)
			{

			}
			FS_SAFE_DEC_REF(f_anim);
		}
	}
	FS_SAFE_DEC_REF(f_animations);

	return sprite;

}

























