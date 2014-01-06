#ifndef _SD_PAINTER_TIME_LINE_H_
#define _SD_PAINTER_TIME_LINE_H_

#include <QRect>
#include <QPainter>
#include <QImage>

class SdTimeLine;
class SdUiButton;

class SdPainterTimeLine
{
	public:
		SdPainterTimeLine();
		~SdPainterTimeLine();

	public:
		int draw(SdTimeLine* timeline,QPainter* painter);

		void setWidth(int width){m_width=width;}
		int getWidth(){return m_width;}

		void setHeight(int height){m_height=height;}
		int getHeight(){return m_height;}

	protected:
        void drawHeadTimeLine(SdTimeLine* timeline,QPainter* painter);
        void drawTranslateTimeLine(SdTimeLine* timeline,QPainter* painter);
        void drawRotateTimeLine(SdTimeLine* timeline,QPainter* painter);
        void drawScaleTimeLine(SdTimeLine* timeline,QPainter* painter);
        void drawColorTimeLine(SdTimeLine* timeline,QPainter* painter);
        void drawOtherTimeLine(SdTimeLine* timeline,QPainter* painter);

	private:
		QImage* mi_eyeShow;
		QImage* mi_eyeHide;

		QImage* mi_expand;
		QImage* mi_collapse;

		QImage* mi_scale;
		QImage* mi_translate;
		QImage* mi_rotate;
		QImage* mi_color;
		QImage* mi_other;


		int m_width;
		int m_height;


		/* rect */
		QRect m_expandRect;
        QRect m_nameRect;
        QRect m_visibleRect;
		QRect m_subIconRect;
		QRect m_subNameRect;

		/* pen */
		QPen m_darkPen;
		QPen m_lightPen;
};



#endif /*_SD_PAINTER_TIME_LINE_H_*/


