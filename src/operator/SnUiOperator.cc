#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <assert.h>
#include <string>

#include "SnUiOperator.h"
#include "SnGlobal.h"
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"
#include "widget/SnInputDialog.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"

SnUiOperator::SnUiOperator()
{
}


SnUiOperator::~SnUiOperator()
{
}


void SnUiOperator::newProject()
{
	
    QString file=QFileDialog::getSaveFileName(
			(QWidget*)NULL,
                QString("Open FScene Project"),
                QString("."),
                QString("FScene File(*.fscene)"));
	
    if(file.length()==0)
    {
        return;
    }

    QFileInfo file_info(file);


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

	SnGlobal::setProject(proj);

}

void SnUiOperator::renameScene()
{
	SnScene* scene=SnGlobal::dataOperator()->getCurScene();

	SnInputDialog dialog("Rename Scene",scene->getName().c_str());

    if(dialog.exec()==QDialog::Accepted)
	{
		std::string name=dialog.getTextField();
		if(name=="")
		{
			QMessageBox msg(QMessageBox::Warning, "Rename Scene","Name Can't Be Empty String");
			msg.exec();
		}
		else 
		{
			if(scene->getName()==name)
			{
				return;
			}
			SnGlobal::dataOperator()->setSceneName(scene,name.c_str());
		}
	} 
}
void SnUiOperator::addLayer2D()
{
	SnInputDialog dialog("Create Layer2D");

    if(dialog.exec()==QDialog::Accepted)
	{
		std::string name=dialog.getTextField();
		if(name=="")
		{
			QMessageBox msg(QMessageBox::Warning, "Create Layer","Name Can't Be Empty String");
			msg.exec();
		}
		else 
		{
			SnLayer2D* layer=new SnLayer2D();
			layer->setName(name);
			SnGlobal::dataOperator()->addLayer2D(layer);
		}
	} 

}


