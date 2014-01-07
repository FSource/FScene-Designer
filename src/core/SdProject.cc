#include "core/SdProject.h"



SdProject* SdProject::create(const std::string& dir,const std::string& name)
{
	return new SdProject(dir,name);
}



std::string SdProject::getName()
{
	return m_projectName;
}


SdSprite* SdProject::createSprite(const char* name)
{
	SdSprite* ret=new SdSprite(name);
	m_sprites->push_back(ret);
	return ret;
}

SdSprite* SdProject::hasSpriteWithName(const char* name)
{
	int size=m_sprites.size();
	for(int i=0;i<size;i++)
	{

	}

}






