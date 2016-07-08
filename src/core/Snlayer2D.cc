
#include "stage/entity/FsEntity2D.h"

#include "support/util/FsArray.h"

#include "SnLayer2D.h"

NS_FS_USE
SnLayer2D::SnLayer2D()
{
	m_array=FsArray::create();
	m_array->addRef();
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






SnLayer2D::~SnLayer2D()
{
	m_array->decRef();
}





