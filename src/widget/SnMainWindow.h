#ifndef _SD_MAIN_WINDOW_H_
#define _SD_MAIN_WINDOW_H_

#include <QString>
#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>

class SnEditViewWidget;
class SnPropertyWidget;

class SnProjectExploreWidget;
class SnResourceExploreWidget;

class SnMainWindow:public QMainWindow
{
	Q_OBJECT
	public:
		SnMainWindow();
		~SnMainWindow();

	public:
		SnEditViewWidget* getEditViewWidget()  {return m_editViewWidget;}
		SnPropertyWidget* getPropertyWidget()  {return m_propertyWidget;}

		SnProjectExploreWidget* getProjectExploreWidget(){return m_projectExploreWidget;}
		QDockWidget* getProjectExploreDockWidget(){return m_projectExploreDockWidget;}

		SnResourceExploreWidget* getResourceExploreWidget(){return m_resourceExploreWidget;}
		QDockWidget* getResourceExploreDockWidget(){return m_resourceExploreDockWidget;}

public:
        void createAboutDialog();

	public slots:
		void onUndo();
		void onRedo();
		void onZoomIn();
		void onZoomOut();

		void onHelp();
		void onAbout();

	protected:
		void initWidget();
        void initLayout();
        void initToolBar();
		void initMenuBar();
    private:

        /* Edit View */
        SnEditViewWidget*  m_editViewWidget;


        /* Property */
        SnPropertyWidget*  m_propertyWidget;

        /* ProjectExplore */
        SnProjectExploreWidget* m_projectExploreWidget;
		QDockWidget* m_projectExploreDockWidget;


        /* ResourceExplore  */
		SnResourceExploreWidget* m_resourceExploreWidget;
		QDockWidget* m_resourceExploreDockWidget;


        /* dialog */
        QDialog* m_aboutDialog;

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

		/* menu about  */
		QMenu* mn_about;
		QAction* ms_help;
		QAction* ms_about_us;
};



#endif /*_SD_MAIN_WINDOW_H_*/


