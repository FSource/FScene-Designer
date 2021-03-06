#ifndef _SD_EDIT_VIEW_WIDGET_H_
#define _SD_EDIT_VIEW_WIDGET_H_ 

#include "GL/glew.h"
#include <QGLWidget>
#include <QCursor>


#include "math/FsVector2.h"
#include "graphics/FsColor.h"
#include "SnEnums.h"
class SnController;
class SnIdentify;
NS_FS_USE


class SnEditViewWidget:public QGLWidget
{
	Q_OBJECT 
	public:
		SnEditViewWidget();
		~SnEditViewWidget();

	public:
		virtual void initializeGL();
		virtual void resizeGL(int width,int height);
		virtual void paintGL();

		virtual void dragEnterEvent(QDragEnterEvent *event);
		virtual void dropEvent(QDropEvent * event);

	public:
		void setController(SnController* cn);

		void translate(Vector2 t);
        void setTranslate(Vector2  t);

		Vector2 getTranslate();
		void setZoom(float s);
		float getZoom();
		void resetZoomTranslate();

		Vector2 toWidgetCoord(Vector2 v);
		Vector2 toEditCoord(Vector2 v);
		void getEditArea(Vector2* a,Vector2* b);



	public:
		void drawAxis();
		void drawGrid();
		void drawScene();
		void drawSelectIdentify();

		void drawEditModeInfo();

		void drawTranslateInfo(Color c,Color c_x,Color c_y,SN_TranslateMode mode);
		void drawResizeInfo(Faeris::Color c,int hit_pos);
		void drawRotateInfo(Color c,float angle);
		void drawScaleInfo(Color cc,Color cx,Color cy,float lx,float ly);


		void drawRect(const Vector2& p,float width,float height);
		void drawBoundBox(SnIdentify* sn,const Color3f& c);

		void drawSelectAreaInWidgetCoord(const Vector2& start,const Vector2& end);


	public:
		void setShowAxis(bool enable);
		bool isShowAxis();


		void setShowGrid(bool enable);
		bool isShowGrid();
		void setGridSize(Vector2 size);
		Vector2 getGridSize();
		void setGridColor(Color a,Color b);

		void setBackgroundColor(Color c);
		Color getBackgroundColor();



	public slots:
		void onZoomIn();
		void onZoomOut();

		void onEditModeChange(SN_EditMode mode);
		void onAxisModeChange(SN_TranslateMode mode);


		void slotIdentifyAttributeChange(SnIdentify* id,const char* name);
		void slotCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st);
		void slotCurProjectChange();



	protected:
		void updateViewMatrix();
		
	private:
		Vector2 m_translate;
		float m_zoom;

		bool m_showAxis;

		bool m_showGrid;
		Vector2 m_gridSize;
		Color m_gridColorA,m_gridColorB;

		Color m_backgroundColor;


		bool m_spaceDown;
		QPoint m_lastpos;
		QCursor m_prevCursor;

		SnController* m_controller;

		SN_EditMode m_editMode;
		SN_TranslateMode m_translateMode;
		SnController* m_moveViewController;
		SnController* m_selectController;
		SnController* m_translateController;
		SnController* m_wtranslateController;
		SnController* m_rotateController;
		SnController* m_resizeController;
		SnController* m_scaleController;



    public: 

		virtual void wheelEvent(QWheelEvent* event);

		virtual void mouseMoveEvent(QMouseEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);
		virtual void mouseReleaseEvent(QMouseEvent* event);
		virtual void keyPressEvent(QKeyEvent* event);
		virtual void keyReleaseEvent(QKeyEvent* event);

};

#endif /*_SD_EDIT_VIEW_WIDGET_H_*/


