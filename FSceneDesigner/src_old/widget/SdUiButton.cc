#include "widget/SdUiButton.h"


SdUiButton::SdUiButton(QRect& rect,const char* image)
{
	m_rect=rect;
    m_image=new QImage(image);
}


SdUiButton::~SdUiButton()
{
    delete m_image;
}



bool SdUiButton::hit(int x,int y)
{
    return m_rect.contains(x,y);
}


void SdUiButton::draw(QPainter* painter)
{
    painter->drawImage(m_rect,*m_image);
}
