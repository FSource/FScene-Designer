#ifndef _SD_DATA_OPERATOR_H_
#define _SD_DATA_OPERATOR_H_
#include <string>
#include <vector>
#include "stage/entity/FsEntity2D.h"
class SnProject;
class SnScene;
class SnLayer2D;
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

		void addLayer2D(SnLayer2D* layer);

		void reindexLayer2D(SnLayer2D* layer,int index);
		void moveEntityToLayer(Faeris::Entity2D* en,SnLayer2D* layer);
			
		void	moveEntityToEntity(Faeris::Entity2D* en,Faeris::Entity2D* p);


		/* redo/undo */ 
		bool canRedo();
		bool canUndo();
		void redo();
		void undo();
};


#endif /*_SD_DATA_OPERATOR_H_*/


