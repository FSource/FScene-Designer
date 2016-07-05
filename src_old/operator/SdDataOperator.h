#ifndef _SD_DATA_OPERATOR_H_
#define _SD_DATA_OPERATOR_H_
#include <string>
#include <vector>

class SdProject;
class SdSprite;
class SdAnimation;

class SdDataOperator
{
	public:
		SdDataOperator();
		~SdDataOperator();

	public:
		/* project */
		SdProject* getCurProject();
		void setCurProject(SdProject* proj);

		/*  sprite */
		void setCurSprite(SdSprite* sprite);
		SdSprite* getCurSprite();

		SdSprite* createSprite(SdProject* proj,const std::string& name);
		void addSprite(SdProject* proj,SdSprite* sprite,int pos);
		void removeSprite(SdProject* proj,SdSprite* sprite);

		void setSpriteName(SdSprite* sprite,const std::string& name);

		/* animation */
		void setCurAnimation(SdAnimation* anim);
		SdAnimation* getCurAnimation();

		void setAnimationName(SdAnimation* anim,const std::string& name);

		SdAnimation* createAnimation(SdSprite* sprite,const std::string& name);

		void addAnimation(SdSprite* sprite,SdAnimation* anim,int pos);
		void removeAnimation(SdSprite* sprite,SdAnimation* anim);

		/* redo/undo */ 
		bool canRedo();
		bool canUndo();
		void redo();
		void undo();
};


#endif /*_SD_DATA_OPERATOR_H_*/


