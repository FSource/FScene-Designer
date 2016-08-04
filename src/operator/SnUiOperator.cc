#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <assert.h>
#include <string>

#include "SnUiOperator.h"
#include "SnIoOperator.h"
#include "SnGlobal.h"
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"
#include "dialog/SnInputDialog.h"
#include "dialog/SnNewProjectDialog.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"
#include "SnTest.h"

SnUiOperator::SnUiOperator()
{
}


SnUiOperator::~SnUiOperator() 
{
}


void SnUiOperator::newProject()
{
	SnNewProjectDialog  dialog;
	if(dialog.exec()!=QDialog::Accepted)
	{
		return;
	}	

	SnProject* proj= SnProject::create();
	
	proj->setDirName(dialog.getFilePath());
	proj->setFileName(dialog.getFileName());
	proj->setName(dialog.getFileName());
	SnGlobal::setProject(proj);

}

void SnUiOperator::openProject()
{

	QString file=QFileDialog::getOpenFileName(
			(QWidget*)NULL,
			QString("Open FScene Project"),
			QString("."),
			QString("FScene File(*.fscene)"));

	if(file.length()==0)
	{
		return;
	}

	SnProject* proj=SnGlobal::ioOperator()->loadProject(SnUtil::qtostd(file).c_str());

	if(proj==NULL)
	{
		QMessageBox msg(QMessageBox::Warning,"Open Project","Open Project Failed");
		msg.exec();
		return ;
	}

	SnGlobal::setProject(proj);

}


void SnUiOperator::renameScene()
{
	SnScene* scene=SnGlobal::dataOperator()->getCurScene();

	SnInputDialog dialog("Rename Scene",scene->getIdentifyName());

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
			if(std::string(scene->getIdentifyName())==name)
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
			layer->setIdentifyName(name.c_str());
			SnGlobal::dataOperator()->addLayer2D(layer);
		}
	} 

}


