#include "sys/io/FsSysFile.h"
#include "support/util/FsArray.h"
#include "support/util/FsDict.h"
#include "support/util/FsString.h"
#include "support/util/FsScriptUtil.h"
NS_FS_USE

#include "io/SdProjectLoader.h"
#include "core/SdProject.h"
#include "core/SdSprite.h"
#include "core/SdAnimation.h"
#include "core/SdTimeLine.h"
#include "core/SdSubTimeLine.h"
#include "core/SdSubTimeLineSet.h"
#include "core/SdImageMgr.h"



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
                SdAnimation* anim=parseAnimation(f_anim);
				if(anim)
				{
					sprite->addAnimation(anim);
				}
			}
			FS_SAFE_DEC_REF(f_anim);
		}
	}
	FS_SAFE_DEC_REF(f_animations);

	return sprite;

}

SdAnimation* SdProjectLoader::parseAnimation(FsDict* dict)
{

	FsString* f_name=ScriptUtil::getString(dict,"name");
	if(!f_name)
	{
		return NULL;
	}
    SdAnimation* anim=new SdAnimation(f_name->cstr());
	FS_SAFE_DEC_REF(f_name);


	int play_speed;

	if(ScriptUtil::getInteger(dict,"playSpeed",&play_speed))
	{
		anim->setPlaySpeed(play_speed);
	}


	FsDict* f_timeline=ScriptUtil::getDict(dict,"timeline");
	if(f_timeline)
	{
		SdTimeLine* timeline=parseTimeLine(f_timeline);
		if(timeline)
		{
			anim->addTimeLine(timeline);
		}
	}
	FS_SAFE_DEC_REF(f_timeline);

	return anim;
}

SdTimeLine* SdProjectLoader::parseTimeLine(FsDict* dict)
{

    FsString* f_name=ScriptUtil::getString(dict,"name");
    if(!f_name)
    {
        return NULL;
    }


    SdTimeLine* timeline=new SdTimeLine(f_name->cstr());
    FS_SAFE_DEC_REF(f_name);


	FsDict* f_scale=ScriptUtil::getDict(dict,"scale");
	if(f_scale)
	{

		SdScaleTimeLine* scale=parseScaleTimeLine(f_scale);
		if(scale)
		{
			timeline->setScaleTimeLine(scale);
		}
	}
	FS_SAFE_DEC_REF(f_scale);


	FsDict* f_translate=ScriptUtil::getDict(dict,"translate");
	if(f_translate)
	{
		SdTranslateTimeLine* translate=parseTranslateTimeLine(f_translate);
		if(translate)
		{
			timeline->setTranslateTimeLine(translate);
		}
	}
	FS_SAFE_DEC_REF(f_translate);

	FsDict* f_rotate=ScriptUtil::getDict(dict,"rotate");
	if(f_rotate)
	{
		SdRotateTimeLine* rotate=parseRotateTimeLine(f_rotate);
		if(rotate)
		{
			timeline->setRotateTimeLine(rotate);
		}
	}
	FS_SAFE_DEC_REF(f_rotate);


	FsDict* f_color=ScriptUtil::getDict(dict,"color");
	if(f_color)
	{
		SdColorTimeLine* color=parseColorTimeLine(f_color);
		if(color)
		{
			timeline->setColorTimeLine(color);
		}
	}
	FS_SAFE_DEC_REF(f_color);

	FsDict* f_other=ScriptUtil::getDict(dict,"other");
	if(f_other)
	{
		SdOtherTimeLine* other=parseOtherTimeLine(f_other);
		if(other)
		{
			timeline->setOtherTimeLine(other);
		}
	}
	FS_SAFE_DEC_REF(f_other);

	return timeline;
}

SdScaleTimeLine* SdProjectLoader::parseScaleTimeLine(FsDict* dict)
{
    SdScaleTimeLine* line=new SdScaleTimeLine();

	FsArray* f_keyframes=ScriptUtil::getArray(dict,"keyFrames");
	if(f_keyframes)
	{
		int size=f_keyframes->size();
		for(int i=0;i<size;i++)
		{

			SdScaleKeyFrame frame;

			FsDict* f_frame=ScriptUtil::getDict(f_keyframes,i);
			if(!f_frame) { continue; }

			ScriptUtil::getInteger(f_frame,"index",&frame.m_index);
			ScriptUtil::getFloat(f_frame,"x",&frame.m_scaleX);
			ScriptUtil::getFloat(f_frame,"y",&frame.m_scaleY);
            line->insertKeyFrame(frame);

			FS_SAFE_DEC_REF(f_frame);
		}
	}
	FS_SAFE_DEC_REF(f_keyframes);
    return line;
}

SdTranslateTimeLine* SdProjectLoader::parseTranslateTimeLine(FsDict* dict)
{
    SdTranslateTimeLine* line=new SdTranslateTimeLine();
	FsArray* f_keyframes=ScriptUtil::getArray(dict,"keyFrames");

	if(f_keyframes)
	{
		int size=f_keyframes->size();
		for(int i=0;i<size;i++)
		{
			SdTranslateKeyFrame frame;
			FsDict* f_frame=ScriptUtil::getDict(f_keyframes,i);
			if(!f_frame){continue;}
			ScriptUtil::getInteger(f_frame,"index",&frame.m_index);
			ScriptUtil::getFloat(f_frame,"x",&frame.m_translateX);
			ScriptUtil::getFloat(f_frame,"y",&frame.m_translateY);
            line->insertKeyFrame(frame);
			FS_SAFE_DEC_REF(f_frame);
		}
	}

	FS_SAFE_DEC_REF(f_keyframes);
    return line;




}
SdRotateTimeLine* SdProjectLoader::parseRotateTimeLine(FsDict* dict)
{
	SdRotateTimeLine* line=new SdRotateTimeLine();
	FsArray* f_keyframes=ScriptUtil::getArray(dict,"keyFrames");

	if(f_keyframes)
	{
		int size=f_keyframes->size();
		for(int i=0;i<size;i++)
		{
            SdRotateKeyFrame frame;
			FsDict* f_frame=ScriptUtil::getDict(f_keyframes,i);
			if(!f_frame){continue;}
			ScriptUtil::getInteger(f_frame,"index",&frame.m_index);
			ScriptUtil::getFloat(f_frame,"angle",&frame.m_angle);
            line->insertKeyFrame(frame);
			FS_SAFE_DEC_REF(f_frame);
		}
	}

	FS_SAFE_DEC_REF(f_keyframes);
	return line;
}

SdOtherTimeLine* SdProjectLoader::parseOtherTimeLine(FsDict* dict)
{

	SdOtherTimeLine* line=new SdOtherTimeLine();
	FsArray* f_keyframes=ScriptUtil::getArray(dict,"keyFrames");

	if(f_keyframes)
	{
		int size=f_keyframes->size();
		for(int i=0;i<size;i++)
		{
            SdOtherKeyFrame frame;

			FsDict* f_frame=ScriptUtil::getDict(f_keyframes,i);
			if(!f_frame){continue;}
			ScriptUtil::getInteger(f_frame,"index",&frame.m_index);
			ScriptUtil::getFloat(f_frame,"anchorX",&frame.m_anchorX);
			ScriptUtil::getFloat(f_frame,"anchorY",&frame.m_anchorY);
			ScriptUtil::getBoolean(f_frame,"visible",&frame.m_visible);
			ScriptUtil::getFloat(f_frame,"texCoordX0",&frame.m_texCoordX0);
			ScriptUtil::getFloat(f_frame,"texCoordX1",&frame.m_texCoordX1);
			ScriptUtil::getFloat(f_frame,"texCoordY0",&frame.m_texCoordY0);
			ScriptUtil::getFloat(f_frame,"texCoordY1",&frame.m_texCoordY1);


			FsString* f_image=ScriptUtil::getString(f_frame,"image");

			if(f_image)
			{
				SdImage* image=m_curProject->getImageMgr()->load(f_image->cstr());
				frame.m_image=image;
			}
			FS_SAFE_DEC_REF(f_image);
            line->insertKeyFrame(frame);
			FS_SAFE_DEC_REF(f_frame);
		}
	}

	FS_SAFE_DEC_REF(f_keyframes);
	return line;
}

SdColorTimeLine* SdProjectLoader::parseColorTimeLine(FsDict* dict)
{
	SdColorTimeLine* line=new SdColorTimeLine();
	FsArray* f_keyframes=ScriptUtil::getArray(dict,"keyFrames");

	if(f_keyframes)
	{
		int size=f_keyframes->size();
		for(int i=0;i<size;i++)
		{
            SdColorKeyFrame frame;
			FsDict* f_frame=ScriptUtil::getDict(f_keyframes,i);
			if(!f_frame){continue;}
			ScriptUtil::getInteger(f_frame,"index",&frame.m_index);
			ScriptUtil::getInteger(f_frame,"red",&frame.m_red);
			ScriptUtil::getInteger(f_frame,"green",&frame.m_green);
			ScriptUtil::getInteger(f_frame,"blue",&frame.m_blue);
			ScriptUtil::getInteger(f_frame,"alpha",&frame.m_alpha);
            line->insertKeyFrame(frame);
			FS_SAFE_DEC_REF(f_frame);
		}
	}

	FS_SAFE_DEC_REF(f_keyframes);
	return line;
}


































