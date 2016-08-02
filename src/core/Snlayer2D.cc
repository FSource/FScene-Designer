
#include "stage/entity/FsEntity2D.h"

#include "support/util/FsArray.h"
#include "stage/FsScene.h"

#include "SnLayer2D.h"
#include "util/SnUtil.h"

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


SnIdentify* SnLayer2D::getIdentifyParent()
{
	Faeris::Scene* sn=getScene();
	SnIdentify* id= dynamic_cast<SnIdentify*>(sn);
	return id;
}

int SnLayer2D::getIdentifyChildNu()
{
	return m_array->size();
}

SnIdentify* SnLayer2D::getIdentifyChild(int index)
{
	Faeris::Entity2D* en=(Entity2D*)m_array->get(index);
	SnIdentify* id=dynamic_cast<SnIdentify*>(en);
	return id;
}

int SnLayer2D::getIdentifyChildIndex(SnIdentify* id)
{
	Entity2D* en=dynamic_cast<Entity2D*>(id);
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


bool SnLayer2D::isDragEnabled()
{
	return true;
}

bool SnLayer2D::isDropEnabled()
{
	return true;
}


void SnLayer2D::addIdentifyChild(SnIdentify* idenfy)
{
	Entity2D* en=dynamic_cast<Entity2D*>(idenfy);
	Layer2D::add(en);
	m_array->push(en);

}

void SnLayer2D::removeIdentifyChild(SnIdentify* idenfy)
{
	Entity2D* en=dynamic_cast<Entity2D*>(idenfy);
	Layer2D::remove(en);
	m_array->remove(en);


}

void SnLayer2D::clearIdentifyChild()
{
	Layer2D::clearEntity();
	m_array->clear();
}

std::vector<SnIdentify*> SnLayer2D::getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse)
{
	std::vector<SnIdentify*> ret;

	int size=m_array->size();
	for(int i=0;i<size;i++)
	{
   		Entity2D* en=(Entity2D*)m_array->get(i);
		SnIdentify* id=dynamic_cast<SnIdentify*>(en);
		if(SnUtil::identifyInRect(id,start,end))
		{
			ret.push_back(id);
		}

		if(traverse)
		{
			std::vector<SnIdentify*> r=id->getChildInArea(start,end,traverse);
			ret.insert(ret.end(),r.begin(),r.end());
		}
	}

	return ret;
}
SnIdentify* SnLayer2D::getChildHitPoint(Faeris::Vector2f p,bool traverse)
{

	int size=m_array->size();
	for(int i=size-1;i>=0;i--)
	{
   		Entity2D* en=(Entity2D*)m_array->get(i);
		SnIdentify* id=dynamic_cast<SnIdentify*>(en);
	

		if(traverse)
		{
			SnIdentify* ret= id->getChildHitPoint(p,traverse);
			if(ret)
			{
				return ret;
			}
		}

		if(SnUtil::identifyHitPoint(id,p))
		{
			return id;
		}
	}
	return NULL;

}



SnLayer2D::~SnLayer2D()
{
	m_array->decRef();
}





