#include <QDate>
#include "sys/io/FsSysFile.h"
NS_FS_USE

#include "io/SdProjectWriter.h"
#include "core/SdProject.h"
#include "core/SdImage.h"


#include "io/SdProjectLoader.h"
#include "core/SdProject.h"
#include "core/SdSprite.h"
#include "core/SdAnimation.h"
#include "core/SdTimeLine.h"
#include "core/SdSubTimeLine.h"
#include "core/SdSubTimeLineSet.h"

SdProjectWriter::SdProjectWriter()
{

}

SdProjectWriter::~SdProjectWriter()
{

}

bool SdProjectWriter::saveProject(const std::string& filename,SdProject* proj)
{
    FsFile* file=SysFile::create(filename.c_str(),FsFile::FS_IO_WRONLY|FsFile::FS_IO_TRUNC);

	if(file==NULL)
	{
		return false;
	}

	file->writeStr("type:\"FSpriteDesigner2\"\n");
	file->writeStr("version:\"2.0\"\n");

	file->writeStr("project:{\n");
	writeProject(file,"\t",proj);
	file->writeStr("}\n");

	file->writeStr("abouts:{\n");
	writeAbout(file,"\t",proj);
    file->writeStr("}\n\n");
    file->decRef();
    return true;
}


bool SdProjectWriter::writeProject(FsFile* file,const std::string& prefix,SdProject* proj)
{
	std::string next_prefix=prefix+"\t";

	const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();

	file->writeStr("%sname:\"%s\"\n",c_prefix,proj->getName().c_str());
	file->writeStr("%sconfigs:{\n",c_prefix);
	file->writeStr("%sresourceDir:\"%s\"\n",c1_prefix,proj->getResourceDir().c_str());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%ssprites:[\n",c_prefix);

	int size=proj->getSpriteNu();

	for(int i=0;i<size;i++)
	{
		SdSprite* sprite=proj->getSprite(i);

		file->writeStr("%s{\n",c1_prefix);
		writeSprite(file,prefix+"\t\t",sprite);
        file->writeStr("%s}\n",c1_prefix);

	}

	file->writeStr("%s]\n",c_prefix);
	return true;
}

bool SdProjectWriter::writeSprite(FsFile* file,const std::string& prefix,SdSprite* sprite)
{
	std::string next_prefix=prefix+"\t";
	const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();

	file->writeStr("%sname:\"%s\"\n",c_prefix,sprite->getName().c_str());
	file->writeStr("%sanimations:[\n",c_prefix);
    int size=sprite->getAnimationNu();
	for(int i=0;i<size;i++)
	{
		file->writeStr("%s{\n",c1_prefix);
        SdAnimation* anim=sprite->getAnimation(i);
		writeAnimation(file,prefix+"\t\t",anim);
		file->writeStr("%s}\n",c1_prefix);
	}
	file->writeStr("%s]\n",c_prefix);
	return true;
}


bool SdProjectWriter::writeAnimation(FsFile* file,const std::string& prefix,SdAnimation* anim)
{
    //std::string next_prefix=prefix+"\t";
    //const char* c1_prefix=next_prefix.c_str();
    const char* c_prefix=prefix.c_str();

	file->writeStr("%sname:\"%s\"\n",c_prefix,anim->getName().c_str());
	file->writeStr("%splaySpeed:%d\n",c_prefix,anim->getPlaySpeed());
    file->writeStr("%stimelines:[\n",c_prefix);

    int size=anim->getTimeLineNu();
    for(int i=0;i<size;i++)
    {
        writeTimeLine(file,prefix+"\t\t",anim->getTimeLine(i));
    }


    file->writeStr("%s}\n",c_prefix);
    return true;
}


bool SdProjectWriter::writeTimeLine(FsFile* file,const std::string& prefix,SdTimeLine* line)
{
    //std::string next_prefix=prefix+"\t";
    //const char* c1_prefix=next_prefix.c_str();
    const char* c_prefix=prefix.c_str();

	file->writeStr("%stranslate:{\n",c_prefix);
    writeTranslateTimeLine(file,prefix+"\t\t",line->getTranslateTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%sscale:{\n",c_prefix);
    writeScaleTimeLine(file,prefix+"\t\t",line->getScaleTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%srotate:{\n",c_prefix);
    writeRotateTimeLine(file,prefix+"\t\t",line->getRotateTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%scolor:{\n",c_prefix);
    writeColorTimeLine(file,prefix+"\t\t",line->getColorTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%sother:{\n",c_prefix);
    writeOtherTimeLine(file,prefix+"\t\t",line->getOtherTimeLine());
	file->writeStr("%s}\n",c_prefix);
	return true;
}



bool SdProjectWriter::writeTranslateTimeLine(FsFile* file,const std::string& prefix,SdTranslateTimeLine* line)
{
    std::string next_prefix=prefix+"\t";

	const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);
	
	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{
		SdTranslateKeyFrame k=line->getKeyFrame(i);
		file->writeStr("%s{index:%d,x:%f,y:%f}\n",c1_prefix,k.m_index,k.m_translateX,k.m_translateY);
	}

	file->writeStr("%s]\n",c_prefix);
	return true;
}

bool SdProjectWriter::writeScaleTimeLine(FsFile* file,const std::string& prefix,SdScaleTimeLine* line)
{
    std::string next_prefix=prefix+"\t";

    const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);
	
	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{
		SdScaleKeyFrame k=line->getKeyFrame(i);
		file->writeStr("%s{index:%d,x:%f,y:%f}\n",c1_prefix,k.m_index,k.m_scaleX,k.m_scaleY);
	}
	file->writeStr("%s]\n",c_prefix);
	return true;
}
bool SdProjectWriter::writeRotateTimeLine(FsFile* file,const std::string& prefix,SdRotateTimeLine* line)
{
    std::string next_prefix=prefix+"\t";

	const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);

	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{
        SdRotateKeyFrame k=line->getKeyFrame(i);
		file->writeStr("%s{index:%d,angle:%f}\n",c1_prefix,k.m_index,k.m_angle);
	}
	file->writeStr("%s]\n",c_prefix);
	return true;
}
bool SdProjectWriter::writeColorTimeLine(FsFile* file,const std::string& prefix,SdColorTimeLine* line)
{
    std::string next_prefix=prefix+"\t";

	const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);


	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{
        SdColorKeyFrame k=line->getKeyFrame(i);
		file->writeStr("%s{index:%d,red:%d,green:%d,blue:%d,alpha:%d}\n",c1_prefix,k.m_index,k.m_red,k.m_green,k.m_blue,k.m_alpha);

	}

    file->writeStr("%s]\n",c_prefix);
    return true;
}

bool SdProjectWriter::writeOtherTimeLine(FsFile* file,const std::string& prefix,SdOtherTimeLine* line)
{
    std::string next_prefix=prefix+"\t";

	const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);

	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{

        SdOtherKeyFrame k=line->getKeyFrame(i);
		std::string c_visible;
		std::string c_image;

		if(k.m_visible) 
		{
            c_visible="true";
		}
		else
		{
            c_visible="false";
		}

        if(k.m_image)
		{
            c_image=k.m_image->getUrl();
		}

        file->writeStr("%s{index:%d,anchorX:%f,anchorY:%f,visible:%s,texCoordX0:%f,texCoordY0:%f,texCoordX1:%f,texCoordY1:%f,image:\"%s\"}",
                       c1_prefix,k.m_index,k.m_anchorX,k.m_anchorY,c_visible.c_str(),k.m_texCoordX0,k.m_texCoordY0,k.m_texCoordX1,k.m_texCoordY1,c_image.c_str());
	}

    file->writeStr("%s]\n",c_prefix);
    return true;
}

bool SdProjectWriter::writeAbout(FsFile* file,const std::string& prefix,SdProject* /*proj*/)
{
    std::string next_prefix=prefix+"\t";

    const char* c_prefix=prefix.c_str();
    const char* c1_prefix=next_prefix.c_str();

	file->writeStr("%ssoftware:{\n",c_prefix);
    file->writeStr("%sname:\"FSpriteDesigner\"\n",c1_prefix);
    file->writeStr("%sversion:\"2.0\"\n",c1_prefix);
    file->writeStr("%surl:\"www.github.com/FSpriteDesigner2.html\"\n",c1_prefix);
    file->writeStr("%sauthor:\"nosiclin@foxmail.com\"\n",c1_prefix);
    file->writeStr("%scopyright:\"nosiclin@foxmail.com\"\n",c1_prefix);
    file->writeStr("%slicense:\"free\"\n",c1_prefix);
    file->writeStr("%s}\n",c_prefix);

    QDate date=QDate::currentDate();
    file->writeStr("%sdata:\"%d-%d-%d\"\n",c_prefix,date.year(),date.month(),date.day());
    return true;

}







