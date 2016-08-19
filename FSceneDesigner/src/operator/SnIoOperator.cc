#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <assert.h>
#include <string>


#include "SnIoOperator.h"
#include "support/util/FsScriptUtil.h"
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"

#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"
#include "core/SnProject.h"
#include "sys/io/FsSysFile.h"

NS_FS_USE


SnIoOperator::SnIoOperator()
{
}

SnIoOperator::~SnIoOperator()
{
}


SnProject* SnIoOperator::loadProject(const char* filename)
{
	QFile f(filename);

	if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  
	{
		return NULL;
	}

	QTextStream txtInput(&f);  
	txtInput.setCodec("UTF-8");

	QString content=txtInput.readAll();
	FsDict* dict=ScriptUtil::parseScriptFromStr(content.toUtf8().constData());

	if(dict==NULL)
	{
		return NULL;
	}

	SnProject* proj= SnProject::create(dict);
	if(proj==NULL)
	{
		return NULL;
	}

	QFileInfo file_info(filename);

	QString file=file_info.absoluteFilePath();

	QString dir_name=file_info.path()+"/";
	QString base_name=file_info.baseName();

	proj->setDirName(dir_name.toUtf8().constData());
	proj->setFileName(file.toUtf8().constData());
	proj->setName(base_name.toUtf8().constData());

	return proj;
}


bool SnIoOperator::saveProject(SnProject* proj,const char* file_path)
{
	FsFile* sys_file=SysFile::create(file_path,FsFile::FS_IO_CREATE|FsFile::FS_IO_TRUNC|FsFile::FS_IO_WRONLY);
	if(sys_file==NULL)
	{
		return false;
	}

	FsDict* dict=proj->takeSaveFst();
	dict->addRef();

	ScriptUtil::saveScript(sys_file,dict,0);
	sys_file->destroy();
	dict->decRef();

	return true;
}


bool SnIoOperator::exportProject(SnProject* proj,const char* file_path)
{
	FsFile* sys_file=SysFile::create(file_path,FsFile::FS_IO_CREATE|FsFile::FS_IO_TRUNC|FsFile::FS_IO_WRONLY);
	if(sys_file==NULL)
	{
		return false;
	}

	FsDict* dict=proj->takeExportFst();
	if(dict==NULL)
	{
		return false;
	}


	dict->addRef();

	ScriptUtil::saveScript(sys_file,dict,0);
	sys_file->destroy();
	dict->decRef();

	return true;
}



bool SnIoOperator::exportProjectToSimulator(SnProject* proj,const char* file_path)
{
	FsFile* sys_file=SysFile::create(file_path,FsFile::FS_IO_CREATE|FsFile::FS_IO_TRUNC|FsFile::FS_IO_WRONLY);
	if(sys_file==NULL)
	{
		return false;
	}

	FsDict* dict=proj->takeExportFst();
	if(dict==NULL)
	{
		return false;
	}

	int rx=proj->getResolutionX();
	int ry=proj->getResolutionY();

	char buf[128];
	sprintf(buf,"%d",rx);
	dict->insert(FsString::create("winWidth"),FsString::create(buf));
	sprintf(buf,"%d",ry);
	dict->insert(FsString::create("winHeight"),FsString::create(buf));

	dict->addRef();

	ScriptUtil::saveScript(sys_file,dict,0);
	sys_file->destroy();
	dict->decRef();

	return true;
}



