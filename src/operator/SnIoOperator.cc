#include "SnIoOperator.h"
#include "support/util/FsScriptUtil.h"

NS_FS_USE


SnIoOperator::SnIoOperator()
{
}

SnIoOperator::~SnIoOperator()
{
}


SnProject* SnIoOperator::loadProject(const char* filename)
{
	FsDict* dict=ScriptUtil::parse(filename);

	if(dict==NULL)
	{
		return NULL;
	}

	SnProject* proj=new SnProject(dict);

    QFileInfo file_info(filename);

    file=file_info.absoluteFilePath();
    QString dir_name=file_info.path()+"/";
    QString file_name=file_info.fileName();
	QString base_name=file_info.baseName();

    SnProject* proj=new SnProject();
	std::string t_dir=dir_name.toUtf8().constData();
	std::string t_file=file_name.toUtf8().constData();
	std::string t_basename=base_name.toUtf8().constData();
	
	proj->setDirName(t_dir);
    proj->setFileName(t_file);
	proj->setName(t_basename);

	return proj;
}



