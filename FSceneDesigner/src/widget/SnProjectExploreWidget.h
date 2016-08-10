#ifndef _SD_PROJECT_EXPLORE_WIDGET_H_
#define _SD_PROJECT_EXPLORE_WIDGET_H_ 

#include <QWidget>
#include <QTreeView>

class SnProjectExploreModel;
class SnProject;
class SnLayer2D;
class SnIdentify;

class SnProjectExploreWidget:public QWidget
{
	Q_OBJECT
	public:
		SnProjectExploreWidget();
		~SnProjectExploreWidget();

	public slots:
		void clicked(const QModelIndex& index);
		void mousePress(const QModelIndex& index);
		void onProjectChange();
		void slotLayer2DAdd(SnLayer2D* ly);
		void slotIdentifyAdd(SnIdentify* id);
		void slotCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st);
		void slotIdentifyDelete(std::vector<SnIdentify*> st);



	protected:
		void initWidget();
		void initMenu();
		void destory();
		void connectSignal();

    private:
        QTreeView* m_projectExploreView;
		SnProjectExploreModel* m_projectExploreModel;

		/* pop up menu */

		/*  ---  scene---*/
		QMenu* m_menuScene;
		QAction* ma_newLayer2D;
		QAction* ma_renameScene;
		QAction* ma_exportSceneFst;

		/*  ---- layer2d---- */
		QMenu* m_menuLayer2D;
		QAction* ma_newEntity;
		QAction* ma_renameLayer2D;
		QAction* ma_cloneLayer2D;

		QAction* ma_exportLayer2DFst;
		QAction* ma_deleteLayer2D;



};


#endif /*_SD_PROJECT_EXPLORE_WIDGET_H_*/





