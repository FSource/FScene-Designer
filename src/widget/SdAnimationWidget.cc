#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include "widget/SdAnimationWidget.h"
#include "widget/SdUiTimeLineHeader.h"
#include "SdConfig.h"


SdAnimationWidget::SdAnimationWidget()
{
	setMinimumHeight(SD_UI_ANIMATION_WIDGET_MIN_HEIGHT); 

	initWidget();
}

SdAnimationWidget::~SdAnimationWidget()
{

}

void SdAnimationWidget::initWidget()
{
    m_header=new SdUiTimeLineHeader();
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
    painter.drawLine(40,0,40,w_height);




}



