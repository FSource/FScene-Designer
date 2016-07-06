#include <assert.h>
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"

#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"

SnDataOperator::SnDataOperator()
{
}

SnDataOperator::~SnDataOperator()
{
}


SnProject* SnDataOperator::getCurProject()
{
    return SnGlobal::getProject();
}


void SnDataOperator::setCurProject(SnProject* proj)
{
    SnGlobal::setProject(proj);
	SnGlobal::msgCenter()->emitCurProjectChange();
}

SnScene* SnDataOperator::getCurScene()
{
    SnProject* proj=getCurProject();
    if(proj)
    {
        return proj->getCurScene();
    }
    return NULL;
}



void SnDataOperator::setSceneName(SnScene* sn,std::string name)
{
	sn->setName(name);
}

void SnDataOperator::addLayer2D(SnLayer2D* ly)
{
	getCurScene()->push(ly);

	SnGlobal::msgCenter()->emitLayer2DAdd(ly);
}


/* redo/undo */
bool SnDataOperator::canRedo()
{
	return false;
  //  return SnGlobal::canRedo();
}

bool SnDataOperator::canUndo()
{
	return false;
   // return SnGlobal::canUndo();
}

void SnDataOperator::redo()
{

}

void SnDataOperator::undo()
{

}



