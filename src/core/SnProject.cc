
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

	m_currentIdentify=NULL;

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


void SnProject::setCurrentAndSelectIdentify(SnIdentify* ct,const std::vector<SnIdentify*> select)
{
	m_currentIdentify=ct;
	m_selectIdentifys=select;
}
