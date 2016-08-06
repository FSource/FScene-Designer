#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

#include "widget/SnResourceExploreWidget.h"
#include "core/SnProject.h"
#include "SnGlobal.h"

SnResourceExploreWidget::SnResourceExploreWidget()
{
    init();
    layout();
	slotCurProjectChange();
}
SnResourceExploreWidget::~SnResourceExploreWidget()
{
	destroy();
}

void SnResourceExploreWidget::setNameFilters(const QStringList& list)
{
    m_fileModel->setNameFilters(list);
}

void SnResourceExploreWidget::slotCurProjectChange()
{
	SnProject* proj=SnGlobal::getProject();
	if(!proj)
	{
		m_resourceView->setModel(NULL);
		return;
	}
	
	QModelIndex root=m_fileModel->setRootPath(proj->getDirName().c_str());
	m_resourceView->setModel(m_fileModel);
	m_resourceView->setRootIndex(root);
	m_resourceView->setColumnHidden(1,true);
	m_resourceView->setColumnHidden(2,true);
	m_resourceView->setColumnHidden(3,true);
}
void SnResourceExploreWidget::slotFileSelect(const QModelIndex& index)
{
	QFileInfo file_info=m_fileModel->fileInfo(index);
	if(file_info.isDir())
	{
		return ;
	}

	/*
	QString file_name=file_info.filePath();
	QString file_relative_name=MdUtil::toProjectPath(file_name);
	emit signalFileSelect(file_relative_name);

	FS_TRACE_WARN("file_name=%s",file_relative_name.toStdString().c_str());
	*/
}

void SnResourceExploreWidget::init()
{
	m_fileModel=new QFileSystemModel();
	m_fileModel->setReadOnly(true);
	m_fileModel->setFilter(QDir::AllDirs|QDir::Files|QDir::NoSymLinks|QDir::NoDotAndDotDot );
	m_fileModel->setNameFilterDisables(false);

	m_resourceView=new QTreeView(this);
	m_resourceView->setHeaderHidden(true);

}
void SnResourceExploreWidget::layout()
{
	QVBoxLayout* vlayout=new QVBoxLayout;
	vlayout->addWidget(m_resourceView);
	vlayout->setSpacing(0);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);
}

void SnResourceExploreWidget::destroy()
{
	delete m_fileModel;
	delete m_resourceView;
}


