#ifndef _SD_DATA_OPERATOR_H_
#define _SD_DATA_OPERATOR_H_
#include <string>
#include <vector>

class SnProject;
class SnScene;

class SnDataOperator
{
	public:
		SnDataOperator();
		~SnDataOperator();

	public:
		/* project */
		SnProject* getCurProject();
		void setCurProject(SnProject* proj);

		SnScene* getCurScene();
		void setSceneName(SnScene*,std::string name);


		/* redo/undo */ 
		bool canRedo();
		bool canUndo();
		void redo();
		void undo();
};


#endif /*_SD_DATA_OPERATOR_H_*/


