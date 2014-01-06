#ifndef _SD_UI_BUTTON_H_
#define _SD_UI_BUTTON_H_
#include <QRect>
#include <QPainter>
#include <QImage>

class SdUiButton
{
	public:
		SdUiButton(QRect& rect,const char* image);
		~SdUiButton();

	public:
		bool hit(int x,int y);
		void draw(QPainter* painter);

	private:
		QRect m_rect;
        QImage* m_image;
};

#endif /*_SD_UI_BUTTON_H_*/

