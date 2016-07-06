#include <assert.h>

#include "widget/SnProjectExploreModel.h"
#include "core/SnProject.h"
#include "SnGlobal.h"
#include "core/SnIdentify.h"
#include "core/SnScene.h"


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

	SnIdentify* idfier=(SnIdentify*) parent.internalPointer();

    switch(idfier->identifyType())
	{
		case SN_CLASS_SCENE:
			{
				return QModelIndex();
			}
	}
	return QModelIndex();

}

QModelIndex SnProjectExploreModel::parent(const QModelIndex& child) const 
{
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
			}
	}
	return QVariant();
}




void SnProjectExploreModel::refresh()
{
	emit layoutChanged();
}












