#include <QMessageBox>
#include <QFileDialog>

#include "SnNewProjectDialog.h"
#include "util/SnUtil.h"


SnNewProjectDialog::SnNewProjectDialog()
{
	m_dialog.setupUi(this);
	m_dialog.ok_button->setEnabled(false);
}


std::string SnNewProjectDialog::getFileName()
{
	QString text=m_dialog.project_name->text();
	return SnUtil::qtostd(text);
}

std::string SnNewProjectDialog::getFilePath()
{
	QString text=m_dialog.project_path->text();
	return SnUtil::qtostd(text);
}

int SnNewProjectDialog::getResolutionX()
{
	return m_dialog.resolution_x->value();

}

int SnNewProjectDialog::getResolutionY()
{
	return m_dialog.resolution_y->value();
}



void SnNewProjectDialog::projectPathChange(QString value) 
{

	if(m_dialog.project_name->text().size()==0 || 
			m_dialog.project_path->text().size()==0 )
	{
		m_dialog.ok_button->setEnabled(false);
		return;
	}

	QDir path(m_dialog.project_path->text());
	if(!path.exists())
	{
		m_dialog.ok_button->setEnabled(false);
		return ;
	}

	m_dialog.ok_button->setEnabled(true);
}

void SnNewProjectDialog::openFilePath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
			".",
			QFileDialog::ShowDirsOnly
			| QFileDialog::DontResolveSymlinks);
	if(dir.length()==0)
	{
		return;
	}


	m_dialog.project_path->setText(dir);

}




