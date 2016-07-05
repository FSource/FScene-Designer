#include <QtGlobal>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDockWidget>
#include "widget/SdMainWindow.h"
#include "widget/SdAnimationTitleBar.h"
#include "SdGlobal.h"


SdAnimationTitleBar::SdAnimationTitleBar()
{

    m_preHeight=-1;
	m_toggle=true;
	initWidget();
    connectSignal();
}


SdAnimationTitleBar::~SdAnimationTitleBar()
{

}


void SdAnimationTitleBar::initWidget()
{
	/* tile bar */
    QWidget* widget=new QWidget();
    m_ui=new Ui_AnimationTitleBar;
    m_ui->setupUi(widget);


	/* layout */

    QHBoxLayout* h_layout=new QHBoxLayout();
    h_layout->addWidget(widget,1,Qt::AlignLeft );

    h_layout->setContentsMargins(10,0,0,5);


    setLayout(h_layout);

}




void SdAnimationTitleBar::connectSignal()
{
    connect(m_ui->m_expand,SIGNAL(clicked()),this,SLOT(onToggle()));
}


void SdAnimationTitleBar::onToggle()
{

	QDockWidget* dock=SdGlobal::getMainWindow()->getAnimationDockWidget();
	if(!m_toggle)
	{
        dock->setFixedHeight(QWIDGETSIZE_MAX);
		if(m_preHeight!=-1)
		{
			dock->resize(dock->size().width(),m_preHeight);
		}
        m_ui->m_expand->setIcon(QIcon(":images/icon/down.png"));


	}
	else 
	{
        m_preHeight=dock->size().height();
        //qDebug("m_preHeight=%d",m_preHeight);

		QSize rect=size();

        /*
        QPropertyAnimation*  animation=new QPropertyAnimation(dock,"maximumHeight");
        animation->setDuration(250);
		animation->setStartValue(m_preHeight);
		animation->setEndValue(rect.height());
        animation->start();
        */

        dock->setFixedHeight(rect.height());

        m_ui->m_expand->setIcon(QIcon(":images/icon/up.png"));
	}
	m_toggle=!m_toggle;
}











