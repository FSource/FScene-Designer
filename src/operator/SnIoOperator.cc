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
	QString file_name=file_info.fileName();
	QString base_name=file_info.baseName();

	std::string t_dir=dir_name.toUtf8().constData();
	std::string t_file=file_name.toUtf8().constData();
	std::string t_basename=base_name.toUtf8().constData();

	proj->setDirName(t_dir);
	proj->setFileName(t_file);
	proj->setName(t_basename);
	return proj;
}



