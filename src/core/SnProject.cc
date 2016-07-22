

#include "SnScene.h"
#include "core/SnEntity2D.h"
#include "core/SnProject.h"

NS_FS_USE

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
	m_currentLayer=NULL;

	m_editMode=SN_EditMode::TRANSALTE;

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
	if(ct!=NULL)
	{
		if(dynamic_cast<SnScene*>(ct))
		{
			m_currentLayer=NULL;
		}
		else if(dynamic_cast<SnLayer2D*>(ct))
		{
			m_currentLayer=dynamic_cast<SnLayer2D*>(ct);
		}
		else if(dynamic_cast<Entity2D*>(ct))
		{
			Entity2D* en=dynamic_cast<Entity2D*>(ct);
			Layer2D* l=(Layer2D*)en->getLayer();
			m_currentLayer=dynamic_cast<SnLayer2D*>(l);
		}
	}

	m_currentIdentify=ct;
	m_selectIdentifys=select;

	m_selectIdentifysRoots.clear();

	int size=m_selectIdentifys.size();

	for(int i=0;i<size;i++)
	{
		SnIdentify* id=m_selectIdentifys[i];

		bool push_back=true;
		for(int j=0;j<size;j++)
		{
			if(id->isAncestors(m_selectIdentifys[j]))
			{
				
				push_back=false;
			}
		}
		if(push_back)
		{
			m_selectIdentifysRoots.push_back(id);
		}
	}
}













