#include <assert.h>

#include "widget/SnProjectExploreModel.h"
#include "core/SnProject.h"


SnProjectExploreModel::SnProjectExploreModel()
{
}

SnProjectExploreModel::~SnProjectExploreModel()
{
}


QModelIndex SnProjectExploreModel::index(int row,
		int column,const QModelIndex& parent) const 
{

		return QModelIndex(); 

}

QModelIndex SnProjectExploreModel::parent(const QModelIndex& child) const 
{
	return QModelIndex();
}

int SnProjectExploreModel::rowCount(const QModelIndex& parent)const 
{
	return 0;
}

int SnProjectExploreModel::columnCount(const QModelIndex& /*parent*/)const
{
	return 1;
}


QVariant SnProjectExploreModel::data(const QModelIndex& index,int role)const 
{
	return QVariant();
}




void SnProjectExploreModel::refresh()
{
	emit layoutChanged();
}












