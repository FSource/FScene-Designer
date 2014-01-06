#include "widget/SdUiTimeLineHeader.h"
#include "widget/SdUiButton.h"
#include "SdConfig.h"


static const int S_ButtonWidth=16;
static const int S_ButtonHeight=16;

SdUiTimeLineHeader::SdUiTimeLineHeader()
{

	m_height=SD_UI_TIME_LINE_HEADER_HEIGHT;
	m_rulerStartValue=0;
	m_width=0;

	initUi();
}


void SdUiTimeLineHeader::initUi()
{
    int button_y=(SD_UI_TIME_LINE_HEADER_HEIGHT-S_ButtonHeight)/2;

	m_new=new SdUiButton(QRect(20,button_y,S_ButtonWidth,S_ButtonHeight),":images/icon/new.png");
	m_delete=new SdUiButton(QRect(50,button_y,S_ButtonWidth,S_ButtonHeight),":images/icon/remove.png");

	m_toFront=new SdUiButton(QRect(100,button_y,S_ButtonWidth,S_ButtonHeight),":images/icon/tofront.png");
	m_forward=new SdUiButton(QRect(130,button_y,S_ButtonWidth,S_ButtonHeight),":images/icon/toup.png");
	m_backward=new SdUiButton(QRect(160,button_y,S_ButtonWidth,S_ButtonHeight),":images/icon/toback.png");
	m_toEnd=new SdUiButton(QRect(190,button_y,S_ButtonWidth,S_ButtonHeight),":images/icon/toend.png");

}

void SdUiTimeLineHeader::draw(QPainter* painter)
{
	m_new->draw(painter);
	m_delete->draw(painter);

	m_toFront->draw(painter);
	m_forward->draw(painter);
	m_backward->draw(painter);
	m_toEnd->draw(painter);

	drawRuler(painter);
}

void SdUiTimeLineHeader::drawRuler(QPainter* painter)
{
	int max_rulervalue=m_width/SD_UI_ANIMATION_RULER_GAP;

	int start_x =SD_UI_ANIMATION_RULER_START;
	int step_x=SD_UI_ANIMATION_RULER_GAP;

	int text_y=m_height/2;
	char buf[100];
	for (int i=0;i<max_rulervalue;i++)
	{
        int height;
		int value=i+m_rulerStartValue;

		if (value % 5 == 0 )
		{
			sprintf(buf,"%d",value);
            height=m_height/2.5;
        	painter->drawText(QRect(start_x-30,text_y-30,60,60),Qt::AlignHCenter|Qt::AlignVCenter,buf);
		}
		else 
		{
			height=m_height/4;
		}


        painter->drawLine(start_x,m_height-height,start_x,m_height);
		start_x+=step_x;
	}
}

void SdUiTimeLineHeader::setWidth(int width)
{
	m_width=width;
}

int SdUiTimeLineHeader::getWidth()
{
	return m_width;
}

void SdUiTimeLineHeader::setHeight(int height)
{
	m_height=height;
}

int SdUiTimeLineHeader::getHeight()
{
	return m_height;
}







