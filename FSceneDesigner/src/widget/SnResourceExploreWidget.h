#ifndef _MD_RESOURCE_WIDGET_H_
#define _MD_RESOURCE_WIDGET_H_

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QModelIndex>

class SnFileIconProvider;


class SnResourceExploreWidget:public QWidget
{
	Q_OBJECT
	public:
		SnResourceExploreWidget();
        ~SnResourceExploreWidget();
    public:
        void setNameFilters(const QStringList& list);

    signals:
        void signalFileSelect(const QString& file_name);

	public slots:
        void slotCurProjectChange();
        void slotFileSelect(const QModelIndex& index);

	protected:
		void init();
        void destroy();
        void layout();

	private:
		QFileSystemModel* m_fileModel;
		QTreeView* m_resourceView;
		SnFileIconProvider* m_fileIconProvider;
};

#endif /*_MD_RESOURCE_WIDGET_H_*/

