#include <QHBoxLayout>
#include <QPixmap>
#include "widget/SdAnimationTitleBar.h"

SdAnimationTitleBar::SdAnimationTitleBar()
{

	m_toggle=false;
	initWidget();
	initLayout();
}


void SdAnimationTitleBar::initWidget()
{
	/* expand button */
	m_expand=new QPushButton();
	m_expand->setIcon(QIcon(":images/icon/IDI_EXPAND"));
	m_expand->setFlat(true);
	m_expand->setFixedSize(QSize(16,16));

	/* Animation Label */
    m_lable=new QLabel("Animation");
}



void SdAnimationTitleBar::initLayout()
{

	QHBoxLayout* h_layout=new QHBoxLayout;
	h_layout->setContentsMargins(0,0,0,0);

	h_layout->addSpacing(10);
	h_layout->addWidget(m_expand,0,Qt::AlignLeft);
    h_layout->addWidget(m_lable,0,Qt::AlignLeft);

	setLayout(h_layout);
}





SdAnimationTitleBar::~SdAnimationTitleBar()
{

}
