
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
	m_scene->setName(name);
}

SnScene* SnProject::getCurScene()
{
	return m_scene;
}









