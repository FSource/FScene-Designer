
#include "stage/entity/FsEntity2D.h"

#include "support/util/FsArray.h"
#include "stage/FsScene.h"

#include "SnLayer2D.h"

NS_FS_USE
SnLayer2D::SnLayer2D()
{
	m_array=FsArray::create();
	m_array->addRef();
}
int SnLayer2D::identifyType()
{
	return SN_CLASS_LAYER2D;
}
const char* SnLayer2D::identifyTypeName()
{
	return "SnLayer2D";
}


void SnLayer2D::add(Entity* en) 
{
	Layer2D::add(en);
	m_array->push(en);
}

void SnLayer2D::remove(Entity* en)
{
	Layer2D::remove(en);
	m_array->remove(en);
}

void SnLayer2D::clearEntity()
{
	Layer2D::clearEntity();
	m_array->clear();
}


int SnLayer2D::getEntityNu()
{
	return m_array->size();
}

Entity2D*  SnLayer2D::getEntity(int index)
{
	return (Entity2D*) m_array->get(index);
}

int SnLayer2D::getEntityIndex(Faeris::Entity* en)
{
	int size=m_array->size();
	for(int i=0;i<size;i++)
	{
		if(en==m_array->get(i))
		{
			return i;
		}
	}
	return 0;
}



SnIdentify* SnLayer2D::getIdentifyParent()
{
	Faeris::Scene* sn=getScene();
	SnIdentify* id= dynamic_cast<SnIdentify*>(sn);
	return id;
}

int SnLayer2D::getIdentifyChildNu()
{
	return getEntityNu();
}

SnIdentify* SnLayer2D::getIdentifyChild(int index)
{
	Faeris::Entity2D* en=getEntity(index);
	SnIdentify* id=dynamic_cast<SnIdentify*>(en);
	return id;
}

int SnLayer2D::getIdentifyChildIndex(SnIdentify* id)
{
	Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>(id);
	return getEntityIndex(en);

}


bool SnLayer2D::isDragEnabled()
{
	return true;
}

bool SnLayer2D::isDropEnabled()
{
	return true;
}




SnLayer2D::~SnLayer2D()
{
	m_array->decRef();
}





