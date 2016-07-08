#include "FsEnums.h"


#include <assert.h>
#include <QPixmap>
#include <QIcon>
#include <QMimeData>

#include "widget/SnProjectExploreModel.h"
#include "core/SnProject.h"
#include "SnGlobal.h"
#include "SnMacros.h"
#include "operator/SnDataOperator.h"
#include "core/SnIdentify.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"
#include "core/SnEntity2D.h"




#define SN_SCENE_MIME_TYPE  "SnSceneMimeType"

NS_FS_USE


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

		SnLayer2D* layer=(SnLayer2D*)sn->getLayer(layer_nu-1-row);

		return createIndex(row,column,layer);
	}
	else if(dynamic_cast<SnLayer2D*>(idfier))
	{
		SnLayer2D* sn=(SnLayer2D*)idfier;
		int entity_nu=sn->getEntityNu();
		if(row>=entity_nu)
		{
			return QModelIndex();
		}

		Entity2D* en=(Entity2D*)sn->getEntity(row);
		return createIndex(row,column,en);
	}
	else if(dynamic_cast<Entity2D*>(idfier))
	{
		Entity2D* en=(Entity2D*) idfier;
		int child_nu=en->getChildNu();
		if(row>=child_nu)
		{
			return QModelIndex();
		}

		Entity2D* ch=(Entity2D*) en->getChild(row);
		return createIndex(row,column,ch);
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
	else if(dynamic_cast<Entity2D*>(idfier))
	{
		Entity2D* en=(Entity2D*)idfier;
		if(en->getParent()==NULL)
		{
			return createIndex(0,0,en->getLayer());
		}
		else 
		{
			return createIndex(0,0,en->getParent());
		}
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
	else if(dynamic_cast<SnLayer2D*>(idfier))
	{
		SnLayer2D* layer=(SnLayer2D*) idfier;
		int entity_nu=layer->getEntityNu();
		return entity_nu;

	}
	else if(dynamic_cast<Entity2D*>(idfier))
	{
		Entity2D* en=(Entity2D*) idfier;
		int child_nu=en->getChildNu();
		return child_nu;
	}

	return 0;
}

int SnProjectExploreModel::columnCount(const QModelIndex& /*parent*/)const
{
	return 2;
}

QVariant SnProjectExploreModel:: headerData(int section, Qt::Orientation , int role) const
{
	if (role != Qt::DisplayRole) 
	{
		return QVariant(); 
	}

	if (section ==0 )
	{
		return QString("Name");
	}
	else if(section==1)
	{
		return QString("Visible");
	}
	return QVariant();

}

QVariant SnProjectExploreModel::data(const QModelIndex& index,int role)const 
{
	if(!index.isValid())
	{
		return QVariant();
	}

	if(index.column()==0)
	{
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

					else if(dynamic_cast<SnEntity2D*>(idfier))
					{
						return QString(((SnEntity2D*)idfier)->getName().c_str());
					}
					break;
				}
			case Qt::DecorationRole:
				{
					if(dynamic_cast<SnScene*>(idfier))
					{
						return QIcon(SN_DT_SCENE);
					}
					else if(dynamic_cast<SnLayer2D*>(idfier))
					{
						return QIcon(SN_DT_LAYER2D);
					}
					else if(dynamic_cast<Entity2D*>(idfier))
					{
						return QIcon(SN_DT_LAYER2D);
					}
					break;
				}
		}
	}
	else if(index.column()==1)
	{
		FsObject* idfier=(FsObject*)index.internalPointer();
		switch(role)
		{
			case Qt::DecorationRole:
				{
					if(dynamic_cast<SnScene*>(idfier))
					{
						//return QIcon(SN_SHOW);
					}
					else if(dynamic_cast<SnLayer2D*>(idfier))
					{
						return QIcon(SN_SHOW);
					}
					else if(dynamic_cast<Entity2D*>(idfier))
					{
						return QIcon(SN_SHOW);
					}
					break;
				}
		}
	}
	return QVariant();
}



 Qt::ItemFlags SnProjectExploreModel::flags(const QModelIndex &index) const 
{
	if (!index.isValid())
	{
		return Qt::ItemIsEnabled;
	}

	if(index.column()!=0)
	{
		return QAbstractItemModel::flags(index);
	}


	Qt::ItemFlags flags=QAbstractItemModel::flags(index);

	FsObject* idfier=(FsObject*)index.internalPointer();
	if(dynamic_cast<SnScene*>(idfier))
	{
		return flags;
	}
	else if(dynamic_cast<SnLayer2D*>(idfier))
	{
		return flags|Qt::ItemIsDropEnabled|Qt::ItemIsDragEnabled;
	}
	else if(dynamic_cast<Entity2D*>(idfier))
	{
		return flags|Qt::ItemIsDropEnabled|Qt::ItemIsDragEnabled;
	}


	return flags;
}


 Qt::DropActions SnProjectExploreModel::supportedDropActions() const
{
	return QAbstractItemModel::supportedDropActions() | Qt::MoveAction;
}

void SnProjectExploreModel::refresh()
{
	emit layoutChanged();
}

QStringList SnProjectExploreModel::mimeTypes() const
{
	QStringList types;
	types << SN_SCENE_MIME_TYPE;
	return types;
}


QMimeData* SnProjectExploreModel::mimeData(const QModelIndexList &indexes) const
{

	if(indexes.size() != 1 || !indexes[0].isValid())
	{
		return nullptr;
	}


	quintptr nodeAddress = (quintptr)indexes[0].internalPointer();
	QByteArray encodedData(QString::number(nodeAddress).toUtf8());

	QMimeData *mimeData = new QMimeData();
	mimeData->setData(SN_SCENE_MIME_TYPE, encodedData);

	return mimeData;
}




bool SnProjectExploreModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int, const QModelIndex &parent)
{
	// make sure this is aciton shouldn't be ignored
	if(!data || action == Qt::IgnoreAction)
		return false;

	// get the encoded data of our Node pointer
	QByteArray encodedData = data->data(SN_SCENE_MIME_TYPE);
	FsObject* node = (FsObject*)encodedData.toULongLong();
	if(!node) 
	{
		return false;
	}

	// get the parent node
	QModelIndex destinationParentIndex;

	FsObject* parentNode = static_cast<FsObject*>(parent.internalPointer());

	if(parentNode==NULL)
	{
		return false;
	}

	if(dynamic_cast<SnLayer2D*>(node))
	{
		if(row==-1)
		{
			if(dynamic_cast<SnLayer2D*>(parentNode))
			{
				
				SnLayer2D* l_to=(SnLayer2D*) parentNode;

				SnLayer2D* l_from=(SnLayer2D*) node;
				
				Scene* sn=l_to->getScene();
				int l_index=sn->getLayerIndex(l_to);

				SnGlobal::dataOperator()->reindexLayer2D(l_from,l_index);
				return true;
			}
		}
	}
	else if(dynamic_cast<Entity2D*>(node))
	{
		if(row==-1)
		{
			if(dynamic_cast<SnLayer2D*>(parentNode)) 
			{
				Entity2D* en=(Entity2D*) node;
				SnLayer2D* layer=(SnLayer2D*) parentNode;

				if(en->getLayer()==layer&&en->getParent()==NULL)
				{
					return false;
				}
				SnGlobal::dataOperator()->moveEntityToLayer(en,layer);
			}
			else if(dynamic_cast<Entity2D*>(parentNode))
			{
				Entity2D* en=(Entity2D*) node;
				Entity2D* en2=(Entity2D*) parentNode;
				if(en->getParent()==en2)
				{
					return false;
				}
				SnGlobal::dataOperator()->moveEntityToEntity(en,en2);
				return true;
			}
		}
	}
	return false;
}









