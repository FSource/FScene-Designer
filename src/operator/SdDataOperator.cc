#include "operator/SdDataOperator.h"


SdDataOperator::SdDataOperator()
{
}

SdDataOperator::~SdDataOperator()
{
}


SdProject* SdDataOperator::getCurProject()
{
	return SdGlobal::getProject();
}


SdProject* SdDataOperator::setCurProject(SdProject* proj)
{
	SdGlobal::setCurProject(proj);
	SdGlobal::getMsgCenter()->emitCurProjectChange();
}

SdSprite* SdDataOperator::getCurSprite()
{
	SdProject* proj=getCurProject();
	if(proj)
	{
		return proj->getCurSprite();
	}
	return NULL;

}


void SdDataOperator::setCurSprite(SdSprite* sprite)
{
	SdProject* proj=getCurProject();
	assert(proj);
	if(proj)
	{
		proj->setCurSprite(sprite);
	}
	SdGlobal::getMsgCenter()->emitCurSpriteChange();
}


SdSprite* SdDataOperator::createSprite(SdProject* proj,const std::string& name)
{
	SdSprite* sprite=new SdSprite(name);
	addSprite(proj,sprite,proj->getSpriteNu());
	return sprite;
}


void SdDataOperator::addSprite(SdProject* proj,SdSprite* sprite,int pos)
{
	SdSpriteAddCommand* cmd=new SdSpriteAddCommand(proj,sprite,pos);
	proj->pushCommand(cmd);
	cmd->redo();
	cmd->emitRedoSignal();
}



void SdDataOperator::removeSprite(SdProject* proj,SdSprite* sprite)
{
    SdSpriteRemoveCommand* cmd=new SdSpriteRemoveCommand(proj,sprite);
    proj->pushCommand(cmd);
    cmd->redo();
    cmd->emitRedoSignal();

}

void SdDataOperator::setSpriteName(SdSprite* sprite,const char* name)
{

	SdProject* proj=getCurProject();

    SdSpriteAttribute attr_old=sprite->getAttribute();
    SdSpriteAttribute attr_new=sprite->getAttribute();

    attr_new.name=std::string(name);

	SdSpriteAttrChangeCommand* cmd=new SdSpriteAttrChangeCommand(sprite,attr_old,attr_new);

	proj->pushCommand(cmd);
	cmd->redo();
	cmd->emitRedoSignal();
}

SdAnimation* SdDataOperator::getCurAnimation()
{
	SdSprite* sprite=getCurSprite();
	if(sprite)
	{
		return sprite->getCurAnimation();
	}
	return NULL;
}


void SdDataOperator::setCurAnimation(SdAnimation* anim)
{
	SdSprite* sprite=anim->getSprite();

	if(sprite!=getCurSprite())
	{
		SdGlobal::setCurSprite(sprite);
		SdGlobal::setCurAnimation(anim);
		SdGlobal::getMsgCenter()->emitCurSpriteChange();
		SdGlobal::getMsgCenter()->emitCurAnimationChange();
	}
	else 
	{
		SdGlobal::setCurAnimation(anim);
		SdGlobal::getMsgCenter()->emitCurAnimationChange();
	}
}

SdAnimation* SdDataOperator::addAnimation(SdSprite* sprite,const std::string& name)
{
	SdAnimation* anim=new SdAnimation(name);
	int anim_nu=sprite->getAnimationNu();
	addAnimation(sprite,anim,anim_nu);
}

void SdDataOperator::addAnimation(SdSprite* sprite,SdAnimation* anim,int pos)
{
    SdProject* proj=getCurProject();
    SdAnimationAddCommand* cmd=new SdAnimationAddCommand(sprite,anim,pos);
	proj->pushCommand(cmd);
	cmd->redo();
	cmd->emitRedoSignal();
}

void SdDataOperator::removeAnimation(SdSprite* sprite,SdAnimation* anim)
{
	SdProject* proj=getCurProject();
	SdAnimationRemoveCommand* cmd=new SdAnimationRemoveCommand(sprite,anim);
	proj->pushCommand(cmd);
	cmd->redo();
	cmd->emitRedoSignal();
}


/* redo/undo */
bool SdDataOperator::canRedo()
{
	return SdGlobal::canRedo();
}

bool SdDataOperator::canUndo()
{
	return SdGlobal::canUndo();
}

void SdDataOperator::redo()
{
	assert(canRedo());

	SdProject* proj=getCurProject();
	SdCommand* command=proj->redo();
	command->emitRedoSignal();
}

void SdDataOperator::undo()
{
	assert(canUndo());
	SdProject* proj=getCurProject();
	SdCommand* command=proj->undo();
	command->emitUndoSignal();
}





























































