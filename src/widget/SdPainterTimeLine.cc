#include <QRect>
#include "core/SdTimeline.h"

#include "widget/SdPainterTimeLine.h"
#include "SdConfig.h"

SdPainterTimeLine::SdPainterTimeLine()
{
	mi_eyeShow=new QImage(":images/icon/eye_show.png");
	mi_eyeHide=new QImage(":images/icon/eye_hide.png");

	mi_expand=new QImage(":images/icon/expand.png");
	mi_collapse=new QImage(":images/icon/collapse.png");

	mi_scale=new QImage(":images/icon/scale.png");
	mi_translate=new QImage(":images/icon/translate.png");
	mi_rotate=new QImage(":images/icon/rotate.png");


	mi_color=NULL;
	mi_other=NULL;

	m_width=0;
	m_height=SD_UI_ANIMATION_RULER_HEIGHT;



	/* rect */
	m_expandRect= QRect(SD_UI_ANIMATION_RULER_EXPAND_X-SD_UI_COMMON_ICON_SIZE/2,
			m_height/2-SD_UI_COMMON_ICON_SIZE/2,
			SD_UI_COMMON_ICON_SIZE,
			SD_UI_COMMON_ICON_SIZE);
	m_nameRect=QRect(SD_UI_ANIMATION_RULER_NAME_X,
			0,
			SD_UI_ANIMATION_WIDGET_MIN_HEIGHT-SD_UI_ANIMATION_RULER_NAME_X,
			m_height);

	m_visibleRect= QRect(SD_UI_ANIMATION_RULER_EYE_AREA/2-SD_UI_COMMON_ICON_SIZE/2,
						m_height/2-SD_UI_COMMON_ICON_SIZE/2,
						SD_UI_COMMON_ICON_SIZE,
						SD_UI_COMMON_ICON_SIZE
					);

    m_subIconRect = QRect(SD_UI_ANIMATION_SUB_RULER_ICON_X-SD_UI_COMMON_ICON_SIZE/2,
			m_height/2-SD_UI_COMMON_ICON_SIZE/2,
			SD_UI_COMMON_ICON_SIZE,
			SD_UI_COMMON_ICON_SIZE);

    m_subNameRect = QRect(SD_UI_ANIMATION_SUB_RULER_NAME_X,
			0,
            SD_UI_ANIMATION_WIDGET_MIN_HEIGHT-SD_UI_ANIMATION_SUB_RULER_NAME_X,
			m_height);


	/* pen */
    m_darkPen=QPen(QColor(0,0,0));
    m_lightPen=QPen(QColor(171,171,171));



}

SdPainterTimeLine::~SdPainterTimeLine()
{
	if(mi_eyeShow) delete mi_eyeShow;
	if(mi_eyeHide) delete mi_eyeHide;
	if(mi_expand) delete mi_expand;
	if(mi_collapse) delete mi_collapse;
	if(mi_scale) delete mi_scale;
	if(mi_translate) delete mi_translate;
	if(mi_rotate) delete mi_rotate;
	if(mi_color) delete mi_color;
	if(mi_other) delete mi_other;
}




int SdPainterTimeLine::draw(SdTimeLine* timeline,QPainter* painter)
{
	painter->save();
	/* draw header */
	drawHeadTimeLine(timeline,painter);

	/* draw subtimeline */
	if(timeline->getExpand())
	{

		/* translate timeline */
        painter->setPen(m_lightPen);
		painter->drawLine(0,m_height,m_width,m_height);
		painter->translate(0, m_height);
		drawTranslateTimeLine(timeline,painter);


		/* rotate timeline */
        painter->setPen(m_lightPen);
		painter->drawLine(SD_UI_ANIMATION_RULER_EYE_AREA,m_height,m_width,m_height);
		painter->translate(0, m_height);
		drawRotateTimeLine(timeline,painter);

		/* scale timeline */
        painter->setPen(m_lightPen);
		painter->drawLine(SD_UI_ANIMATION_RULER_EYE_AREA,m_height,m_width,m_height);
		painter->translate(0, m_height);
		drawScaleTimeLine(timeline,painter);

		/* color timeline */
        painter->setPen(m_lightPen);
		painter->drawLine(SD_UI_ANIMATION_RULER_EYE_AREA,m_height,m_width,m_height);
		painter->translate(0, m_height);
		drawColorTimeLine(timeline,painter);
		
		/* other timeline */
        painter->setPen(m_lightPen);
		painter->drawLine(SD_UI_ANIMATION_RULER_EYE_AREA,m_height,m_width,m_height);
		painter->translate(0, m_height);
		drawOtherTimeLine(timeline,painter);
	}


    painter->setPen(m_darkPen);
	painter->drawLine(0,m_height,m_width,m_height);

	int offset=30;
	if (timeline->getExpand())
	{
		offset*=6;
	}

	painter->restore();

	return offset;
}




void SdPainterTimeLine::drawHeadTimeLine(SdTimeLine* timeline,QPainter* painter)
{

	/* draw eye */
	if (timeline->getVisible())
	{
        painter->drawImage(m_visibleRect,*mi_eyeShow);
	}
	else 
	{
        painter->drawImage(m_visibleRect,*mi_eyeHide);
	}

	/* draw expand */

	if (timeline->getExpand())
	{
		painter->drawImage(m_expandRect,*mi_collapse);
	}
	else 
	{
		painter->drawImage(m_expandRect,*mi_expand);
	}

	/* draw name */
    painter->drawText(m_nameRect,Qt::AlignLeft|Qt::AlignVCenter,
			timeline->getName().c_str());

}

void SdPainterTimeLine::drawTranslateTimeLine(SdTimeLine* timeline,QPainter* painter)
{

	painter->drawImage(m_subIconRect,*mi_translate);

    painter->setPen(m_darkPen);
    painter->drawText(m_subNameRect,Qt::AlignLeft|Qt::AlignVCenter, "Translate");


}
void SdPainterTimeLine::drawScaleTimeLine(SdTimeLine* timeline,QPainter* painter)
{

	painter->drawImage(m_subIconRect,*mi_scale);
    painter->setPen(m_darkPen);
    painter->drawText(m_subNameRect,Qt::AlignLeft|Qt::AlignVCenter, "Scale");

}

void SdPainterTimeLine::drawRotateTimeLine(SdTimeLine* timeline,QPainter* painter)
{

	painter->drawImage(m_subIconRect,*mi_rotate);
    painter->setPen(m_darkPen);
    painter->drawText(m_subNameRect,Qt::AlignLeft|Qt::AlignVCenter, "Rotate");
}

void SdPainterTimeLine::drawColorTimeLine(SdTimeLine* timeline,QPainter* painter)
{

	painter->drawImage(m_subIconRect,*mi_rotate);
    painter->setPen(m_darkPen);
    painter->drawText(m_subNameRect,Qt::AlignLeft|Qt::AlignVCenter, "Color");
}
void SdPainterTimeLine::drawOtherTimeLine(SdTimeLine* timeline,QPainter* painter)
{

	painter->drawImage(m_subIconRect,*mi_rotate);
    painter->setPen(m_darkPen);
    painter->drawText(m_subNameRect,Qt::AlignLeft|Qt::AlignVCenter, "Other");
}













