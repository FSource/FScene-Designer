#include <QData>
#include "io/SdProjectWriter.h"

SdProjectWriter::SdProjectWriter()
{

}

SdProjectWriter::~SdProjectWriter()
{

}

bool SdProjectWriter::saveProject(const std::string& filename,SdProject* proj)
{
	FsFile* file=SysFile:create(filename.c_str(),FsFile::FS_IO_WRONLY|FsFile::FS_IO_TRUNC);

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
}


bool SdProjectWriter::writeProject(FsFile* file,const std::string& prefix,SdProject* proj)
{
	std::string next_prefix=prefix+"\t";

	const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();

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
		file->writeStr("%s}\n",c1_preifx);

	}

	file->writeStr("%s]\n",c_prefix);
	return true;
}

bool SdProjectWriter::writeSprite(FsFile* file,const std::string& prefix,SdSprite* sprite)
{
	std::string next_prefix=prefix+"\t";
	const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();

	file->writeStr("%sname:\"%s\"\n",c_prefix,sprite->getName().c_str());
	file->writeStr("%sanimations:[\n",c_prefix);
	int size=sprite->getAnimationNU();
	for(int i=0;i<size;i++)
	{
		file->writeStr("%s{\n",c1_prefix);
		SdAnmation* anim=sprite->getAnimation(i);
		writeAnimation(file,prefix+"\t\t",anim);
		file->writeStr("%s}\n",c1_prefix);
	}
	file->writeStr("%s]\n",c_prefix);
	return true;
}

bool SdProjectWriter::writeAnimation(FsFile* file,const std::string& prefix,SdAnmation* anim)
{
	std::string next_prefix=prefix+"\t";
	const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();

	file->writeStr("%sname:\"%s\"\n",c_prefix,anim->getName().c_str());
	file->writeStr("%splaySpeed:%d\n",c_prefix,anim->getPlaySpeed());
	file->writeStr("%stimeline:{\n",c_prefix);

	writeTimeLine(file,prefix,anim->getTimeLine());
	
	file->writeStr("%s}\n",c_prefix);
}


bool SdProjectWriter::writeTimeLine(FsFile* file,const std::string& prefix,SdAnmation* anim)
{
	std::string next_prefix=prefix+"\t";
	const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();

	file->writeStr("%stranslate:{\n",c_prefix);
	writeScaleTimeLine(file,prefix+"\t\t",anim->getTranslateTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%sscale:{\n",c_prefix);
	writeScaleTimeLine(file,prefix+"\t\t",anim->getScaleTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%srotate:{\n",c_prefix);
	writeScaleTimeLine(file,prefix+"\t\t",anim->getRotateTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%scolor:{\n",c_prefix);
	writeScaleTimeLine(file,prefix+"\t\t",anim->getColorTimeLine());
	file->writeStr("%s}\n",c_prefix);

	file->writeStr("%sother:{\n",c_prefix);
	writeScaleTimeLine(file,prefix+"\t\t",anim->getOtherTimeLine());
	file->writeStr("%s}\n",c_prefix);
	return true;
}



bool SdProjectWriter:writeTranslateTimeLine(FsFile* file,const std::string& prefix,SdTranslateTimeLine* line)
{
	std::string next_prefix=prefix+"\t"

	const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);
	
	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{
		SdTranslateKeyFrame k=line->getKeyFrame(i);
		file->writeStr("%s{frame:%d,value:{x:%f,y:%f}}\n",c1_prefix,k.m_index,k.m_translateX,k.m_translateY);
	}

	file->writeStr("%s]\n",c_prefix);
	return true;
}

bool SdProjectWriter::writeScaleTimeLine(FsFile* file,const std::string& prefix,SdScaleTimeLine* line)
{
	std::string next_prefix=prefix+"\t"

	const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();
	file->writeStr("%skeyFrames:[\n",c_prefix);
	
	int size=line->getKeyFrameNu();

	for(int i=0;i<size;i++)
	{
		SdScaleKeyFrame k=line->getKeyFrame(i);
		file->writeStr("%s{frame:%d,value:{x:%f,y:%f}}\n",c1_prefix,k.m_index,k.m_scaleX,k.m_scaleY);
	}
	file->writeStr("%s]\n",c_prefix);
	return true;
}













bool SdProjectWriter::writeAbout(FsFile* file,const std::string& prefix,SdProject* /*proj*/)
{
	std::string next_prefix=prefix+"\t"

		const char* c_prefix=prefix.c_str();
	const char* c1_preifx=next_prefix.c_str();

	file->writeStr("%ssoftware:{\n",c_prefix);
	file->writeStr("%sname:\"FSpriteDesigner\"\n",c1_preifx);
	file->writeStr("%sversion:\"2.0\"\n",c1_preifx);
	file->writeStr("%surl:\"www.github.com/FSpriteDesigner2.html\"\n",c1_preifx);
	file->writeStr("%sauthor:\"nosiclin@foxmail.com\"\n",c1_preifx);
	file->writeStr("%scopyright:\"nosiclin@foxmail.com\"\n",c1_preifx);
	file->writeStr("%slicense:\"free\"\n",c1_preifx);
	file->writeStr("%s}\n",c_preifx);

	QData data=QData::currentData();
	file->writeStr("%sdata:\"%d-%d-%d\"\n",c_prefix,data.year(),data.month(),data.day());

}







