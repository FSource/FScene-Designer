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

	SnIdentify* id=static_cast <SnIdentify*>(parent.internalPointer());

	int children_nu= id->getIdentifyChildNu();
	if(row>=children_nu)
	{
		return QModelIndex();
	}
	SnIdentify* ch=id->getIdentifyChild(row);

	return createIndex(row,column,ch);

}

QModelIndex SnProjectExploreModel::parent(const QModelIndex& child) const 
{
	if(!child.isValid())
	{
		return QModelIndex();
	}

	SnIdentify* idfier=(SnIdentify*)child.internalPointer();

	SnIdentify* parent=idfier->getIdentifyParent();

	if(parent==NULL)
	{
		return QModelIndex();
	}
	else 
	{
		return createIndex(0,0,parent);
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

	

	SnIdentify* idfier=(SnIdentify*)parent.internalPointer();

	return idfier->getIdentifyChildNu();
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
		SnIdentify* idfier=(SnIdentify*)index.internalPointer();
		switch(role)
		{ 
			case Qt::DisplayRole:
				{
					return QString(idfier->getIdentifyName());
					break;
				}
			case Qt::DecorationRole:
				{
		
					return QIcon(SN_DT_LAYER2D);
					break;
				}
		}
	}
	else if(index.column()==1)
	{
		SnIdentify* idfier=(SnIdentify*)index.internalPointer();

		switch(role)
		{
			case Qt::DecorationRole:
				{
					return QIcon(SN_SHOW);
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

	SnIdentify* idfier=(SnIdentify*)index.internalPointer();
	int type=idfier->identifyType();

	if(idfier->isDragEnabled())
	{
		flags|=Qt::ItemIsDragEnabled;
	}

	if(idfier->isDropEnabled())
	{
		flags|=Qt::ItemIsDropEnabled;
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
	SnIdentify* node = (SnIdentify*)encodedData.toULongLong();
	if(!node) 
	{
		return false;
	}

	// get the parent node
	QModelIndex destinationParentIndex;

	SnIdentify* parentNode = static_cast<SnIdentify*>(parent.internalPointer());

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
				
				SnLayer2D* l_to=dynamic_cast<SnLayer2D*>(parentNode);

				SnLayer2D* l_from=dynamic_cast<SnLayer2D*>( node);
				
				Faeris::Scene* sn=l_to->getScene();
				int l_index=sn->getLayerIndex(l_to);

				SnGlobal::dataOperator()->reindexLayer2D(l_from,l_index);
				return true;
			}
		}
	}
	else if(dynamic_cast<Faeris::Entity2D*>(node))
	{
		if(row==-1)
		{
			if(dynamic_cast<SnLayer2D*>(parentNode)) 
			{
				Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>( node);
				SnLayer2D* layer=dynamic_cast<SnLayer2D*>(parentNode);

				if(en->getLayer()==layer&&en->getParent()==NULL)
				{
					return false;
				}
				SnGlobal::dataOperator()->moveEntityToLayer(en,layer);
			}
			else if(dynamic_cast<Faeris::Entity2D*>(parentNode))
			{
				Faeris::Entity2D* en=dynamic_cast<Faeris::Entity2D*>( node);
				Faeris::Entity2D* en2=dynamic_cast<Faeris::Entity2D*>( parentNode);
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


QModelIndex SnProjectExploreModel::getIdentifyModelIndex(SnIdentify* id)
{
	SnIdentify* p=id->getIdentifyParent();
	if(p==NULL)
	{
		return  createIndex(0,0,id);
	}
	else 
	{
		int row=p->getIdentifyChildIndex(id);

		return createIndex(row,0,id);
	}
	return QModelIndex();

}






