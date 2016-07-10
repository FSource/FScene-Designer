#ifndef _SD_PROJECT_EXPLORE_MODEL_H_
#define _SD_PROJECT_EXPLORE_MODEL_H_

#include <QAbstractItemModel>
#include "FsObject.h"

class SnProjectExploreModel:public QAbstractItemModel 
{
	Q_OBJECT
	public:
		SnProjectExploreModel();
		~SnProjectExploreModel();

	public:
		virtual QModelIndex index(int row,int column, const QModelIndex& parent=QModelIndex())const;
		virtual QModelIndex parent(const QModelIndex& child)const;
		virtual int rowCount(const QModelIndex& parent=QModelIndex())const;
		virtual int columnCount(const QModelIndex& parent=QModelIndex())const;
		virtual QVariant data(const  QModelIndex& index, int role=Qt::DisplayRole) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
		virtual Qt::ItemFlags flags(const QModelIndex &index) const;
		virtual QStringList mimeTypes() const;
		virtual QMimeData* mimeData(const QModelIndexList& indexes)const;
		virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int, const QModelIndex &parent);
 		virtual Qt::DropActions supportedDropActions() const;



	public:
		void refresh();
};

#endif /*_SD_PROJECT_EXPLORE_MODEL_H_*/





