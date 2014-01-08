#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include "widget/SdAnimationWidget.h"
#include "widget/SdUiTimeLineHeader.h"
#include "widget/SdPainterTimeLine.h"
#include "core/SdAnimation.h"
#include "core/SdTimeLine.h"
#include "SdConfig.h"


SdAnimationWidget::SdAnimationWidget()
{
	setMinimumHeight(SD_UI_ANIMATION_WIDGET_MIN_HEIGHT); 

	initWidget();
	initTest();
}

SdAnimationWidget::~SdAnimationWidget()
{

}

void SdAnimationWidget::initWidget()
{
    m_header=new SdUiTimeLineHeader();
	m_painterTimeLine=new SdPainterTimeLine();
}

void SdAnimationWidget::initTest()
{

    m_animation=new SdAnimation("ss");

	m_animation->createTimeLine("Head")->setExpand(true);
	m_animation->createTimeLine("Body");
	m_animation->createTimeLine("Leg")->setExpand(true);
	m_animation->createTimeLine("Arm")->setSelect(true);
	m_animation->createTimeLine("Foot");
}



void SdAnimationWidget::paintEvent(QPaintEvent* /*event*/)
{

    QSize s=size();
    int w_width=s.width();
    int w_height=s.height();

	QPen pen;
	pen.setColor(QColor(0,0,0));

	QPainter painter(this);
 	QBrush brush(QColor(204,204,204));

    painter.setBrush(brush);
	//painter.drawRect(0,0,w_width,w_height);


	painter.setPen(pen);


    /* draw begin line */
    painter.drawLine(0,0,w_width,0);
	painter.drawLine(SD_UI_ANIMATION_RULER_START-10,0,SD_UI_ANIMATION_RULER_START-10,w_height);

    /* draw header */
	m_header->setWidth(w_width);
    m_header->draw(&painter);


	int header_height=m_header->getHeight();

    painter.translate(0,header_height);
    painter.drawLine(0,0,w_width,0);
    painter.drawLine(SD_UI_ANIMATION_RULER_EYE_AREA,0,SD_UI_ANIMATION_RULER_EYE_AREA,w_height);


	/* draw time line */

	m_painterTimeLine->setWidth(w_width);
	int timeline_nu=m_animation->getTimeLineNu();

	for (int i=0;i<timeline_nu;i++)
	{
		SdTimeLine* timeline=m_animation->getTimeLine(i);
        int offset_y=m_painterTimeLine->draw(timeline,&painter);
		painter.translate(0,offset_y);
	}
}










