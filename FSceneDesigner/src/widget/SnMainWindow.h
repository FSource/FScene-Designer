#ifndef _SD_MAIN_WINDOW_H_
#define _SD_MAIN_WINDOW_H_

#include <QString>
#include <QMainWindow>
#include <QDockWidget>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QDialog>
#include "SnEnums.h"


class SnEditViewWidget;
class SnPropertyBrowserWidget;

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
		SnPropertyBrowserWidget* getPropertyWidget()  {return m_propertyWidget;}

		SnProjectExploreWidget* getProjectExploreWidget(){return m_projectExploreWidget;}
		QDockWidget* getProjectExploreDockWidget(){return m_projectExploreDockWidget;}

		SnResourceExploreWidget* getResourceExploreWidget(){return m_resourceExploreWidget;}
		QDockWidget* getResourceExploreDockWidget(){return m_resourceExploreDockWidget;}

	public:
		void createAboutDialog();


	public slots:
		void onEditModeChange(SN_EditMode mode);
		void onAxisModeChange(SN_TranslateMode mode);


	public slots:

		/* file */
		void onNewProject();
		void onOpenProject();
		void onSaveProject();
		void onExportProject();



		/* edit */

		void onUndo();
		void onRedo();
		void onZoomIn();
		void onZoomOut();

		/* edit mode */
		void onEditModeChange(QAction* action);

		/* axis mode */
		void onAxisModeChange(QAction* action);


		/* object*/
		void onCreateLayer2D();
		void onCreateEntity2D();
		void onCreateQuad2D();
		void onCreateSprite2D();
		void onCreateLabelTTF();
		void onCreateLabelBitmap();
		void onCreateParticle2D();
		void onCreatePressButton();
		void onCreateToggleButton();
		void onCreateProcessBar();
		void onCreateUiWidget();
		void onCreateScrollView();
		void onCreateListView();
		void onCreatePageView();
		void onCreateDynamicView();

		/* Simulator */
		void onRunInWindow();


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
		SnPropertyBrowserWidget*  m_propertyWidget;
		QDockWidget* m_propertyDockWidget;

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

		/* edit info */
		QAction* mt_translate;
		QAction* mt_scale;
		QAction* mt_rotate;
		QAction* mt_resize;
		QActionGroup* mg_editInfo;

		/* axis info */
		QActionGroup* mg_axis;
		QAction* mt_local;
		QAction* mt_world;


		/* MenuBar*/
		QMenuBar* m_menubar;
		QMenu* mn_file;
		QMenu* mn_edit;  

		QMenu* mn_object;
		QAction* mf_newLayer2D;

		QMenu* mn_newEntity2D;
		QAction* mf_newEntity;
		QAction* mf_newQuad2D;
		QAction* mf_newSprie2D;
		QAction* mf_newLabelTTF;
		QAction* mf_newLabelBitmap;
		QAction* mf_newParticle2D;
		QMenu* mn_newUi;
		QAction* mf_newPressButton;
		QAction* mf_newToggleButton;
		QAction* mf_newProcessBar;
		QAction* mf_newUiWidget;
		QAction* mf_newScrollView;
		QAction* mf_newListView;
		QAction* mf_newPageView;
		QAction* mf_newDynamicView;



		/* view */
		QMenu* mn_view;
		QMenu* mn_animation;

		/* simulateor */
		QMenu* mn_simulator;
		QAction* mf_runWindow;

		/* setting */
		QMenu* mn_setting;




		/* menu about  */
		QMenu* mn_about;
		QAction* ms_help;
		QAction* ms_about_us;
};



#endif /*_SD_MAIN_WINDOW_H_*/


