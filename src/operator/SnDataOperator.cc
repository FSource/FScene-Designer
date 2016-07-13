#include <assert.h>
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"

#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"


NS_FS_USE

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


void SnDataOperator::setCurLayer(SnLayer2D* layer)
{
	if(getCurLayer()==layer)
	{
		return;
	}

	getCurProject()->setCurLayer(layer);

	SnGlobal::msgCenter()->emitCurLayerChange(layer);
}

SnLayer2D* SnDataOperator::getCurLayer()
{
    SnProject* proj=getCurProject();
    if(proj)
    {
		return proj->getCurLayer();
	}
	return NULL;
}


void SnDataOperator::setCurEntity(Entity2D* en)
{

	SnLayer2D* cur_layer=getCurLayer();
	if(getCurLayer()==en->getLayer())
	{
		if(getCurEntity()==en)
		{
			return;
		}
		else 
		{
			getCurProject()->setCurEntity(en);
			SnGlobal::msgCenter()->emitCurEntityChange();
		}
	}
	else 
	{
		getCurProject()->setCurLayer((SnLayer2D*)en->getLayer());
		getCurProject()->  setCurEntity(en);
		SnGlobal::msgCenter()->emitCurLayerChange((SnLayer2D*)en->getLayer());
	}
}

Entity2D* SnDataOperator::getCurEntity()
{

    SnProject* proj=getCurProject();
    if(proj)
    {
		return proj->getCurEntity();
	}
	return NULL;
}








void SnDataOperator::setSceneName(SnScene* sn,std::string name)
{
	sn->setIdentifyName(name.c_str());
}

void SnDataOperator::addLayer2D(SnLayer2D* ly)
{
	getCurScene()->push(ly);

	SnGlobal::msgCenter()->emitLayer2DAdd(ly);
}

void SnDataOperator::reindexLayer2D(SnLayer2D* l_from,int index)
{
	Scene* sn=l_from->getScene();

	l_from->addRef();
	sn->remove(l_from);
	sn->insert(index,l_from);
	l_from->decRef();

	SnGlobal::msgCenter()->emitLayer2DAdd(l_from);
}

void SnDataOperator::moveEntityToLayer(Faeris::Entity2D* en,SnLayer2D* layer)
{
	en->addRef();
	en->detach();
	layer->add(en);
	en->decRef();
	SnGlobal::msgCenter()->emitLayer2DAdd(layer);
}

void SnDataOperator::moveEntityToEntity(Faeris::Entity2D* en,Faeris::Entity2D* p)
{
	en->addRef();
	en->detach();
	p->addChild(en);
	en->decRef();
	SnGlobal::msgCenter()->emitLayer2DAdd(NULL);
}

void SnDataOperator::setIdentifyAttribute(SnIdentify* id,const char* name,const Faeris::FsVariant& value)
{
	id->setAttribute(name,value);
	SnGlobal::msgCenter()->emitIdentifyAttributeChange(id,name);
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



