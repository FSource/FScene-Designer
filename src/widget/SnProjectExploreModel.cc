#include <assert.h>

#include "widget/SnProjectExploreModel.h"
#include "core/SnProject.h"
#include "SnGlobal.h"
#include "core/SnIdentify.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"


SnProjectExploreModel::SnProjectExploreModel()
{
}

SnProjectExploreModel::~SnProjectExploreModel()
{
}


QModelIndex SnProjectExploreModel::index(int row,
		int column,const QModelIndex& parent) const 
{

	SnProject* proj=SnGlobal::getProject();
	if(!proj)
	{
		return QModelIndex(); 
	}

	SnScene* scene=proj->getCurScene();

	if(!parent.isValid())
	{
		return createIndex(row,column,scene);
	}


	FsObject* idfier=(FsObject*) parent.internalPointer();
	if(dynamic_cast<SnScene*>(idfier))
	{
		SnScene* sn=(SnScene*)idfier;
		int layer_nu=sn->layerNu();
		if(row>=layer_nu)
		{
			return QModelIndex();
		}

		SnLayer2D* layer=(SnLayer2D*)sn->getLayer(row);

		return createIndex(row,column,layer);
	}

	return QModelIndex();

}

QModelIndex SnProjectExploreModel::parent(const QModelIndex& child) const 
{
	if(!child.isValid())
	{
		return QModelIndex();
	}

	FsObject* idfier=(FsObject*)child.internalPointer();
	if(dynamic_cast<SnScene*>(idfier))
	{
		return QModelIndex();
	}
	else if(dynamic_cast<SnLayer2D*>(idfier))
	{
		SnLayer2D* layer=(SnLayer2D*)idfier;
		return createIndex(0,0,layer->getScene());
	}

	return QModelIndex();

}

int SnProjectExploreModel::rowCount(const QModelIndex& parent)const 
{
	if(parent.column()>0)
	{
		return 0;
	}

	if(!parent.isValid())
	{
		return 1;
	}


	FsObject* idfier=(FsObject*)parent.internalPointer();

	if(dynamic_cast<SnScene*>(idfier))
	{
		SnScene* sn=(SnScene*)idfier;
		int layer_nu=sn->layerNu();
		return layer_nu;
	}

	return 0;
}

int SnProjectExploreModel::columnCount(const QModelIndex& /*parent*/)const
{
	return 1;
}


QVariant SnProjectExploreModel::data(const QModelIndex& index,int role)const 
{
	if(!index.isValid())
	{
		return QVariant();
	}


	FsObject* idfier=(FsObject*)index.internalPointer();
	switch(role)
	{
		case Qt::DisplayRole:
			{
				if(dynamic_cast<SnScene*>(idfier))
				{
					return QString(((SnScene*)idfier)->getName().c_str());
				}
				else if(dynamic_cast<SnLayer2D*>(idfier))
				{
					return QString(((SnLayer2D*)idfier)->getName().c_str());
				}

			}
	}
	return QVariant();
}




void SnProjectExploreModel::refresh()
{
	emit layoutChanged();
}












