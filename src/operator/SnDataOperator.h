#ifndef _SD_DATA_OPERATOR_H_
#define _SD_DATA_OPERATOR_H_
#include <string>
#include <vector>
#include "stage/entity/FsEntity2D.h"
#include "SnEnums.h"
class SnProject;
class SnScene;
class SnLayer2D;
class SnIdentify;
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


		void setIdentifyCurrentAndSelect(SnIdentify* current,const std::vector<SnIdentify*>& select);

		SnIdentify* getCurrentIdentify();
		SnLayer2D* getCurrentLayer();
		std::vector<SnIdentify*> getSelectedIdentify();
		std::vector<SnIdentify*> getSelectedIdentifyRoot();



		void setIdentifyAttribute(SnIdentify* id,const char* name,const Faeris::FsVariant& value);

		void addLayer2D(SnLayer2D* layer);

		void reindexLayer2D(SnLayer2D* layer,int index);
		void moveEntityToLayer(Faeris::Entity2D* en,SnLayer2D* layer);
			
		void moveEntityToEntity(Faeris::Entity2D* en,Faeris::Entity2D* p);

		/* transform info */
		void translateInWorld(std::vector<SnIdentify*> ids,float x,float y);

		void setEditMode(SN_EditMode mode);
		void setTranslateMode(SN_TranslateMode mode);



		/* redo/undo */ 
		bool canRedo();
		bool canUndo();
		void redo();
		void undo();
};


#endif /*_SD_DATA_OPERATOR_H_*/


