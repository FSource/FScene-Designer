#ifndef _SD_MAIN_WINDOW_H_
#define _SD_MAIN_WINDOW_H_

#include <QString>
#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

class SdEditViewWidget;
class SdAnimationWidget;
class SdPropertyWidget;

class SdProjectExploreWidget;
class SdResourceExploreWidget;

class SdMainWindow:public QMainWindow
{
	Q_OBJECT
	public:
		SdMainWindow();
		~SdMainWindow();

	public:
		SdEditViewWidget* getEditViewWidget()  {return m_editViewWidget;}

		SdAnimationWidget* getAnimationWidget(){return m_animationWidget;}
		QDockWidget* getAnimationDockWidget(){return m_animationDockWidget;}

		SdPropertyWidget* getPropertyWidget()  {return m_propertyWidget;}

		SdProjectExploreWidget* getProjectExploreWidget(){return m_projectExploreWidget;}
		QDockWidget* getProjectExploreDockWidget(){return m_projectExploreDockWidget;}

		SdResourceExploreWidget* getResourceExploreWidget(){return m_resourceExploreWidget;}
		QDockWidget* getResourceExploreDockWidget(){return m_resourceExploreDockWidget;}

	public slots:
		void onUndo();
		void onRedo();
		void onZoomIn();
		void onZoomOut();


	protected:
		void initWidget();
        void initLayout();
        void initToolBar();
		void initMenuBar();
    private:

        /* Edit View */
        SdEditViewWidget*  m_editViewWidget;

        /* Animation */
        SdAnimationWidget* m_animationWidget;
        QDockWidget* m_animationDockWidget;


        /* Property */
        SdPropertyWidget*  m_propertyWidget;

        /* ProjectExplore */
        SdProjectExploreWidget* m_projectExploreWidget;
		QDockWidget* m_projectExploreDockWidget;


        /* ResourceExplore  */
		SdResourceExploreWidget* m_resourceExploreWidget;
		QDockWidget* m_resourceExploreDockWidget;

		/* ToolBar */
		QToolBar* m_toolbar;
		QAction* mt_undo;
		QAction* mt_redo;
		QAction* mt_zoomIn;
		QAction* mt_zoomOut;

		/* MenuBar*/
		QMenuBar* m_menubar;
		QMenu* mn_file;
		QMenu* mn_edit;
		QMenu* mn_view;
		QMenu* mn_animation;
		QMenu* mn_setting;
		QMenu* mn_help;
};



#endif /*_SD_MAIN_WINDOW_H_*/


