#include <QVBoxLayout>
#include <QLabel>
#include "widget/SdAnimationWidget.h"


SdAnimationWidget::SdAnimationWidget()
{
    QLabel* label1=new QLabel("AFDSFASFSA");
    QLabel* label2=new QLabel("AAAAAAAAAA");
    QLabel* label3=new QLabel("BBBBBBBBBB");

    QVBoxLayout* v_layout=new QVBoxLayout;
	v_layout->addWidget(label1,0);
	v_layout->addWidget(label2,0);
	v_layout->addWidget(label3,0);

	setLayout(v_layout);
}

SdAnimationWidget::~SdAnimationWidget()
{
}


