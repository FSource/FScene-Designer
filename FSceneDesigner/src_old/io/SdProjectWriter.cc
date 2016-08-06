#include <QDate>
#include "sys/io/FsSysFile.h"
NS_FS_USE

#include "io/SdProjectWriter.h"
#include "core/SdProject.h"
#include "core/SdImage.h"


#include "io/SdProjectLoader.h"
#include "core/SdProject.h"
#include "core/SdSprite.h"


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

		file->writeStr("%s}\n",c1_prefix);
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







