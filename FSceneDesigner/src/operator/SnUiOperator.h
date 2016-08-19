#ifndef _SD_UI_OPERATOR_H_
#define _SD_UI_OPERATOR_H_
#include <string>
#include <vector>

#include <QObject>
class SnProject;

class SnUiOperator:public QObject
{
	Q_OBJECT

	public:
		SnUiOperator();
		~SnUiOperator();




	public slots:
		void newProject();
		void openProject();
		void saveProject();
		void exportProject();



		void renameScene();
		void addLayer2D();

		void runInWindow();
};


#endif /*_SD_UI_OPERATOR_H_*/


