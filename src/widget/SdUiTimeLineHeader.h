#ifndef _SD_UI_TIME_LINE_HEADER_H_
#define _SD_UI_TIME_LINE_HEADER_H_ 

#include <QPainter>

class SdUiButton;

class SdUiTimeLineHeader
{
	public:
		SdUiTimeLineHeader();
		~SdUiTimeLineHeader();

	public:
		bool hit(int x,int y);
		void draw(QPainter* painter);


		void setHeight(int height);
		int getHeight();

		void setWidth(int width);
		int getWidth();


		void setRulerStartValue(int value);


	protected:
		void initUi();
		void drawRuler(QPainter* painter);

	private:
		int m_height;
		int m_width;

		int m_rulerStartValue;

		SdUiButton* m_new;
		SdUiButton* m_delete;
		SdUiButton* m_toFront;
		SdUiButton* m_forward;
		SdUiButton* m_backward;
		SdUiButton* m_toEnd;
};




#endif /*_SD_TIME_LINE_HEADER_UI_H_*/


