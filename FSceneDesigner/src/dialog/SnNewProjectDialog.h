#ifndef _SN_NEW_PROJECT_DIALOG_H_
#define _SN_NEW_PROJECT_DIALOG_H_ 
#include "ui_new_project.h"
#include <QDialog>
#include <string>

class SnNewProjectDialog:public QDialog 
{
	Q_OBJECT

	public:
		SnNewProjectDialog();

	public:
		std::string getFilePath();
		std::string getFileName();
		int getResolutionX();
		int getResolutionY();


	public slots:
		void projectPathChange(QString);
		void openFilePath();

	private:
		Ui_NewProjectDialog m_dialog;
};



#endif /*_SN_NEW_PROJECT_DIALOG_H_*/


