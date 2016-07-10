
#include "core/SnProject.h"
#include "SnScene.h"

int SnProject::identifyType()
{
	return SN_CLASS_PROJECT;
}
const char* SnProject::identifyName()
{
	return "SnProject";
}



SnProject::SnProject()
{
	m_scene=new SnScene;
}

SnProject::~SnProject()
{
	if(m_scene)
	{
		delete m_scene;
	}
}

void SnProject::setName(std::string name)
{
	m_name=name;
	m_scene->setIdentifyName(name.c_str());
}

SnScene* SnProject::getCurScene()
{
	return m_scene;
}


void SnProject::setCurLayer(SnLayer2D* layer)
{
	m_curlayer=layer;
	m_curEntity=NULL;
}


SnLayer2D* SnProject::getCurLayer()
{
	return m_curlayer;
}

void SnProject::setCurEntity(Faeris::Entity2D* en)
{
	m_curEntity=en;
}

Faeris::Entity2D* SnProject::getCurEntity()
{
	return m_curEntity;
}


